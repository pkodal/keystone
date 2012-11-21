<?php

/**
 * Registry of objects used per-request.
 * This class is a singleton.
 * 
 * This concept might not be needed if we move to APC/memcached.
 * If not though, this class can become a facade for those caching
 * mechanisms to cache across requests.
 */
class Registry
{   
    const APP_CACHE_PREFIX = 'a:';
    const DISTRBUTED_CACHE_PREFIX = 'd:';

    /*** @var Registry*/
    private static $registry = NULL;
	
        /** @var array assoc. array of classname/id -> object instance. */
	private $objectMap;
        
    /** @var Memcache*/
    private $memcache;
	
	/**
	 * Get the per-request Registry 
	 * 
	 * @return Registry
	 */
	public static function getRegistry()
	{
		if (self::$registry == NULL)
		{
			self::createRegistry();
		}
		
		return self::$registry;
	}
	
	/**
	 * Factory method. Create a new Registry.
	 * 
	 * @return void
	 */
	private static function createRegistry()
	{
		self::$registry = new Registry();
	}
	
	private function __construct()
	{
		$this->objectMap = array(); 
        // $this->memcache = new Memcache();
        // $this->memcache->addserver(MEMCACHE_HOST, MEMCACHE_PORT);
	}
	
	/**
	 * Add an object to the registry.
	 * 
	 * @param $id string unique identifier of the object
	 * @param $object mixed the object instance
         * @param $expires(optional) memchache expires timer.
	 * @return void
	 */
	public function store($id, $object, $expires = NULL)
	{
        // if (strpos($id, self::DISTRBUTED_CACHE_PREFIX) !== false)
        // {
        //     if ($expires != NULL)
        //     {
        //         $this->memcache->set($id, $object, MEMCACHE_COMPRESSED, $expires);
        //     }
        //     else
        //     {
        //         $this->memcache->set($id, $object);
        //     }
        // }
        // else if (strpos($id, self::APP_CACHE_PREFIX) !== false)
        // {
        //     //TODO
        // }
        // else
        // {
            $this->objectMap[$id] = $object;
        // }
	}
	
	/**
	 * Fetch an object from the Registry.
	 * 
	 * @param $id string unique identifier of the object
	 * @return mixed the object if found, FALSE otherwise.
	 */
	public function fetch($id)
	{

            // if (strpos($id, self::DISTRBUTED_CACHE_PREFIX) !== false)
            // {
            //     return $this->memcache->get($id);
            // }
            // else if (strpos($id, self::APP_CACHE_PREFIX) !== false)
            // {
            //     //TODO
            // }
            // else
            if (key_exists ($id, $this->objectMap))
            {
                return $this->objectMap[$id];
            }
            
            return false;
	}
        
        
        public function delete($id)
        {
            // if (strpos($id, self::DISTRBUTED_CACHE_PREFIX) !== false)
            // {
            //     return $this->memcache->delete($id);
            // }
            // else if (strpos($id, self::APP_CACHE_PREFIX) !== false)
            // {
            //     //TODO
            // }
            // else 
            if (key_exists ($id, $this->objectMap))
            {
                unset ($this->objectMap[$id]);
            }            
        }
	
	/**
	 * Get the number of objects currently in the Registry.
	 * 
	 * @return integer
	 */
	public function getLocalObjectCount()
	{
		return count($this->objectMap);
	}
	
	/**
	 * Get an associative array mapping the current object ids
	 * to their respective class types.
	 * 
	 * @return array
	 */
	public function getLocalTypeList()
	{
		$typeList = array();
		
		foreach ($this->objectMap as $key => $object)
		{
			$typeList[$key] = get_class($object);
		}
		
		return $typeList;
	}

    public function destroyRegistry()
    {
        // self::$registry->memcache->flush();
        // self::$registry->memcache->close();
        self::$registry = NULL;
    }
}


?>