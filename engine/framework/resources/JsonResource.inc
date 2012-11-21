<?php

/**
 * Encapsulates a JSON encoded response to the client. 
 */
class JsonResource implements Resource
{
	const SUCCESS_FIELD_NAME = 'success';
	const DATA_FIELD_NAME = 'data';
	
	private $jsonArray;

        /**
         * Factory method. Create a new JsonResource with two simple fields:
         * 'data' (to contain arbritrary string content) and 'success' to contain a
         * boolean response indicating success/fail.
         *
         * @param boolean $_success value of the success field (default: false)
         * @param string $_data value of th data field
         * @return JsonResource a new JsonResource object
         * @see JsonResource
         */
	public static function createSimpleJsonResource($_success = true, $_data = NULL)
	{
		$resource = new JsonResource();
		$resource->addField(self::SUCCESS_FIELD_NAME, $_success);
		
		if ($_data !== NULL)
		{
			$resource->addField(self::DATA_FIELD_NAME, $_data);
		}
		
		return $resource;
	}

        /**
         * Create a new JsonResource that encapsulates an array of values to return
         * in a JSON encoded format.
         *
         * @param array $_jsonArray (optional) associative array to use.
         */
	public function __construct($_jsonArray = array())
	{
		$this->jsonArray = $_jsonArray;		
	}

        /**
         * Add a field to the JSON array
         * @param <type> $key key of the item to add
         * @param <type> $value value of the item to add
         */
	public function addField($key, $value)
	{
		$this->jsonArray[$key] = $value;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see framework/Resource#render()
	 */
	public function render()
	{
		return json_encode($this->jsonArray);	
	}
}

?>