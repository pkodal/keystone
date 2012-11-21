<?php

/**
 * Class to simplify using standard PHP templates, and return response as a
 * string.
 */
class Template implements Resource
{
    const APP_PATH = 'app/';
    private $templateFilename; // immutable.
    private $variableBindings;

    /**
     * Create a new template.
     *
     * @param $_templateFilename string filename of the PHP template
     */
    public function __construct($_templateFilename)
    {
        $this->templateFilename = $_templateFilename;
        $this->variableBindings = array();
    }

    /**
     * Render the template to a string.
     *
     * @param $variableArray array optional array of variable bindings.
     * @return string the rendered content.
     */
    public function render($variableArray = NULL)
    {
        if ($variableArray != NULL)
        {
            $this->bindVariables($variableArray);
        }

        foreach (array_keys($this->variableBindings) as $key)
        {
            $$key = $this->variableBindings[$key];
        }

        ob_start();
        include(self::APP_PATH . $this->templateFilename);
        return ob_get_clean();
    }

    public function bindVariable($variableName, $value)
    {
        $this->variableBindings[$variableName] = $value;
    }

    public function bindVariables($variableArray)
    {
        $this->variableBindings = $variableArray;
    }
}

?>