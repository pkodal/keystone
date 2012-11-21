<?php

include_once(realpath(dirname(__FILE__) . '/models/User.inc'));

class TestController extends AnnotatedRestController
{    
	/**
	 * @var EntityManager
	 */
	private $entityManager;

	public function __construct()
	{
		$this->entityManager = Registry::getRegistry()->fetch(ENTITY_MANAGER);
        parent::__construct(false);
	}
	
	/**
	 * @POST
	 * @ResourcePath(path="/new")
	 */
	protected function addUser()
	{
		$user = new User();
		$user->setFirstName("test");
		$user->setLastName("test");
		$user->setPassword("test");
		$user->setPictureUrl("http://test.com/test/picture");

		$this->entityManager->persist($user);
		$this->entityManager->flush();
		
		return JsonResource::createSimpleJsonResource();
	}


   /**
    * @GET
	* @ResourcePath(path="$id")
	*/
	protected function getUser($id)
	{
		$user = $this->entityManager->find('User', $id);
		return JsonResource::createSimpleJsonResource(true, $user->toArray());
	}
}

?>