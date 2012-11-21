<?php

include_once(realpath(dirname(__FILE__) . '/../orm/Doctrine/Common/Annotations/Annotation.php'));
include_once(realpath(dirname(__FILE__) . '/../orm/Doctrine/Common/Annotations/AnnotationException.php'));
include_once(realpath(dirname(__FILE__) . '/../orm/Doctrine/Common/Annotations/AnnotationReader.php'));
include_once(realpath(dirname(__FILE__) . '/../orm/Doctrine/Common/Annotations/Parser.php'));
include_once(realpath(dirname(__FILE__) . '/../orm/Doctrine/Common/Lexer.php'));
include_once(realpath(dirname(__FILE__) . '/../orm/Doctrine/Common/Annotations/Lexer.php'));

include_once(realpath(dirname(__FILE__) . '/../orm/Doctrine/Common/Cache/Cache.php'));
include_once(realpath(dirname(__FILE__) . '/../orm/Doctrine/Common/Cache/AbstractCache.php'));
include_once(realpath(dirname(__FILE__) . '/../orm/Doctrine/Common/Cache/ArrayCache.php'));



include_once(realpath(dirname(__FILE__) . '/RestController.inc'));
include_once(realpath(dirname(__FILE__) . '/annotations/Annotations.inc'));
include_once(realpath(dirname(__FILE__) . '/annotations/ResourcePath.inc'));
include_once(realpath(dirname(__FILE__) . '/annotations/RequestMethods.inc'));
/**
 * Base class for controllers using REST style url mapping through annotations.
 */
class AnnotatedRestController extends RestController
{
    /** @var array of REST paths */
    private $restMappings;

    /** @var map of requestMethodHandlers*/
    private $requestMethodHandlers;

    /** @var ArrayObject of runBeforeHandlers*/
    private $runBeforeClassHandlers;

    /** @var AnnotationReader*/
    private $reader;


    public function __construct($_routeToDefaultHandlerOnError = false)
    {
        $this->reader = new \Doctrine\Common\Annotations\AnnotationReader();
        $this->reader->setDefaultAnnotationNamespace('Framework\Annotations\\');
        $this->restMappings = null;
        $this->runBeforeClassHandlers = null;
        $this->requestMethodHandlers = null;
        parent::__construct($_routeToDefaultHandlerOnError);

    }

    protected function getRestMapping()
    {
        return $this->restMappings;
    }

    protected function getRequestMethodHandlers()
    {
        return $this->requestMethodHandlers;
    }

    protected function _before()
    {
        if (!isset($this->restMappings))
        {
            $this->buildRestPathTree();
        }

        if (!isset($this->runBeforeClassHandlers))
        {
            $this->buildRunBeforeHandlersList();
        }
        $this->executeRunBeforeHandlers();
    }

    private function buildRunBeforeHandlersList()
    {
        $this->runBeforeClassHandlers = new ArrayObject();
        $refClass = new ReflectionClass(get_class($this));
        $annotations = $this->reader->getClassAnnotations($refClass);
        foreach($annotations as $annotation)
        {
            if(is_a($annotation, 'Framework\Annotations\RunBeforeHandler'))
            {
                $annotation->setRestController($this);
                $this->runBeforeClassHandlers->append($annotation);
            }
        }
    }

    private function executeRunBeforeHandlers()
    {
        foreach($this->runBeforeClassHandlers as $handler)
        {
            $handler->runBefore();
        }
    }

    /**
     * build the REST mappings to use for the controller from the annotations on the methods.
     */
    private function buildRestPathTree()
    {
        $this->restMappings = array();
        $this->requestMethodHandlers = array();
        $refClass = new ReflectionClass(get_class($this));

        foreach ($refClass->getMethods() as $method)
        {
            if ($this->useableMethod($method))
            {
                $annotations = $this->reader->getMethodAnnotations($method);
                foreach ($annotations as $anno)
                {
                    // only process ResourcePath's for now. add other annotations as needed and change this to a
                    // dispatcher pattern.
                    if (is_a($anno,'Framework\Annotations\ResourcePath'))
                    {
                        $this->checkMethodParameterNames($anno, $method);
                        $this->addRestMethodToTree($anno, $method);
                    }
                    else if (is_a($anno, 'Framework\Annotations\RequestMethodHandler'))
                    {
                        $this->requestMethodHandlers[$method->getName()] = $anno;
                    }
                }
            }
        }
    }

    /**
     * Check if the wildcards from the resource path are available as method names.
     *
     * @param ResourcePath $path annotation on the method
     * @param ReflectionMethod $method the method to check
     */
    private function checkMethodParameterNames(Framework\Annotations\ResourcePath $path, ReflectionMethod $method)
    {
        $wildCards = $path->getWildcardNames();
        $methodParameterNames = $this->getMethodParameterNames($method);

        foreach ($wildCards as $wildCard)
        {
            if (!in_array($wildCard, $methodParameterNames))
            {
                throw new FrameworkException($method->getDeclaringClass()->getName() . '->' . $method->getName() . 
                        ' is missing the parameter "' . $wildCard . '" declared in the ResourcePath annotation.');
            }
        }
    }

    /**
     * get all the method parameter names in an array.
     *
     * @param ReflectionMethod $method method to check
     * @return array
     */
    private function getMethodParameterNames(ReflectionMethod $method)
    {
        $methodParameterNames = array();
        foreach ($method->getParameters() as $param)
        {
            array_push($methodParameterNames, $param->getName());
        }
        return $methodParameterNames;
    }

    /**
     * Insert a method and associated REST path into the tree.
     * The method name becomes a leaf node, and this method will create all intermediate nodes along the
     * way as appropriate.
     *
     * @param ResourcePath $path the path to the resource to add
     * @param ReflectionMethod $method the method in the controller responsible for this resource.
     */
    private function addRestMethodToTree(Framework\Annotations\ResourcePath $path, ReflectionMethod $method)
    {
        $expandedPath = $path->getPath();

        // initialise
        $arraryRef = &$this->restMappings;
        $key = array_shift($expandedPath);

        foreach ($expandedPath as $path)
        {
            $this->addNodeToTree($arraryRef, $key, $path);

            // increment reference to next connect node (on a lower branch)
            $arraryRef = &$arraryRef[$key];
            $key = $path;
        }

        // insert leaf node, either as a sibling of other nodes (i.e. parent route), or a single leaf node
        if (isset($arraryRef[$key]) && is_array($arraryRef[$key]))
        {
            $arraryRef[$key][self::PARENT_ROUTE] = $method->getName();
        }
        else
        {
            $arraryRef[$key] = $method->getName();
        }
    }

    /**
     * insert a new intermediate (non-leaf) node into the tree.
     *
     * @param mixed $subTree reference to the root node of the sub-tree to add the node to.
     * @param string $parentNode value of the parent node
     * @param string $newNode value of the new node to add.
     */
    private function addNodeToTree(&$subTree, $parentNode, $newNode)
    {
        if (is_array($subTree) && array_key_exists($parentNode, $subTree))
        {
            if (is_array($subTree[$parentNode]) && !array_key_exists($newNode, $subTree[$parentNode]))
            {
                $subTree[$parentNode][$newNode] = '';
            }
            else if (is_string($subTree[$parentNode]) && $subTree[$parentNode] != '')
            {
                $leafNode = $subTree[$parentNode];
                $subTree[$parentNode] = array(self::PARENT_ROUTE => $leafNode, $newNode => '');
            }
        }
        else
        {
            $subTree[$parentNode] = array($newNode => '');
        }
    }

    /**
     * Check if a given method is usable as a REST controller method.
     *
     * @param ReflectionMethod $method method to check
     * @return true if useable, false otherwise.
     */
    private function useableMethod(ReflectionMethod $method)
    {
        return !$method->isPrivate() && !$method->isStatic() && !$method->isAbstract() &&
                $method->getShortName() != 'getRestMapping' &&
                $method->getShortName() != 'defaultHandler' &&
                $method->getShortName() != 'dispatch' &&
                strpos($method->getShortName(), '_') !== 0;
    }
}

?>
