<?php

class DefaultController extends AnnotatedRestController
{    
	/**
	* This will be the root / path of the website.
	*
	* Must return a Resource.
	*/
	public function defaultHandler($params)
	{
		$template = new Template('/homepage/templates/home.tpl.inc');
		$template->bindVariable('name', 'John Smith');
		return $template;
	}
}

?>