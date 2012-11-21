<?php

/**
 * Repesents a resource, capable of being rendered into a form to send 
 * to the client.
 */
interface Resource
{
	/**
	 * Render a resource.
	 * @return string rendered resource to send to client.
	 */
	function render();
}

?>