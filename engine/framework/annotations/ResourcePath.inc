<?php

namespace Framework\Annotations
{
	class ResourcePath extends \Doctrine\Common\Annotations\Annotation
	{
	    public $path;

	    /**
	     * @return array path split into elements.
	     */
	    public function getPath()
	    {
	        if ($this->path[0] == '/')
	        {
	            $this->path = substr($this->path, 1);
	        }

	        return explode("/", $this->path);
	    }

	    /**
	     * @return array containing any wildcard matches within the path.
	     */
	    public function getWildcardNames()
	    {
	        $splitPath = $this->getPath();

	        $wildcards = array();
	        foreach ($splitPath as $pathElement)
	        {
	            if (strlen($pathElement) > 0 && $pathElement[0] == '$')
	            {
	                array_push($wildcards, substr($pathElement, 1));
	            }
	        }

	        return $wildcards;
	    }
	}
}

?>