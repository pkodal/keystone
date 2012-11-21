<?php

/**
 * Represent a 'Widget' - an encapsulation of CSS, JS, and HTML that makes
 * up a component in the UI.  
 */
class WidgetResource implements Resource
{
	private $css;
	private $javascript;
	private $html;

        /**
         * Create a new WidgetResource, encapsulating containing HTML, CSS, and JS.
         *
         * @param string $_html optional HTML content
         * @param string $_css optional CSS filename to include
         * @param string $_javascript optional JS filename to include
         */
	public function __construct($_html = "", $_css = "", $_javascript = "")
	{
		$this->html = $_html;
		$this->css = $_css;
		$this->javascript = $_javascript;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see framework/Resource#render()
	 */
	public function render()
	{
		$widget = "";
		
		if ($this->containsCssFile())
		{
			$widget .= HtmlUtil::includeCss($this->css); 
		}
		
		if ($this->containsJavascriptFile())
		{
			$widget .= HtmlUtil::includeScript($this->javascript);
		}
				
		$widget .= $this->html;
		return $widget;
	}

        /**
         * @param string $_html HTML to set.
         */
	public function setHtml($_html)
	{
		$this->html = $_html;
	}

        /**
         * @param string $_jsFile JS file to set.
         */
	public function setJavascriptFile($_jsFile)
	{
		$this->javascript = $_jsFile;
	}

        /**
         * @param string $_cssFile CSS file to set
         */
	public function setCssFile($_cssFile)
	{
		$this->css = $_cssFile;
	}

        /**
         * @return string HTML content
         */
	public function getHtml()
	{
		return $this->html;
	}

        /**
         * @return string CSS filename
         */
	public function getCssFile()
	{
		return $this->css;
	}

        /**
         * @return string JS filename
         */
	public function getJavascriptFile()
	{
		return $this->javascript;
	}

        /**
         * @return boolean true if this resource contains an attached CSS file
         */
	public function containsCssFile()
	{
		if (is_array($this->css) && count($this->css))
			return true;
			
		return (strlen($this->css) > 0);
	}

        /**
         * @return boolean true if this resource contains an attached JS file
         */
	public function containsJavascriptFile()
	{
		if (is_array($this->javascript) && count($this->javascript))
			return true;
			
		return (strlen($this->javascript) > 0);
	}
}

?>