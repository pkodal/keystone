<?php
namespace Framework\Annotations
{
	include_once(realpath(dirname(__FILE__) . '/Annotations.inc'));

	class GET extends RequestMethodHandler
	{
	    public function runHandler()
	    {
	      	if ($_SERVER['REQUEST_METHOD'] != 'GET')
	      	{
	      		throw new \Exception("Invalid Request");
	      	}

	      	return true;
	    }
	}

	class POST extends RequestMethodHandler
	{
	    public function runHandler()
	    {
	      	if ($_SERVER['REQUEST_METHOD'] != 'POST')
	      	{
	      		throw new \Exception("Invalid Request");
	      	}

	      	return true;
	    }
	}

	class PUT extends RequestMethodHandler
	{
	    public function runHandler()
	    {
	      	if ($_SERVER['REQUEST_METHOD'] != 'PUT')
	      	{
	      		throw new \Exception("Invalid Request");
	      	}

	      	return true;
	    }
	}

	class DELETE extends RequestMethodHandler
	{
	    public function runHandler()
	    {
	      	if ($_SERVER['REQUEST_METHOD'] != 'DELETE')
	      	{
	      		throw new \Exception("Invalid Request");
	      	}

	      	return true;
	    }
	}
}
?>