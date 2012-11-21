<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 * Description of SchemaGenerator
 *
 * @author tima
 */
class SchemaGenerator
{
    /** @var SchemaTool*/
    private $tool;
    
    /** @var EntityManager*/
    private $entityManager;

    public function  __construct()
    {
        $this->entityManager = Registry::getRegistry()->fetch(ENTITY_MANAGER);
        $this->tool = new \Doctrine\ORM\Tools\SchemaTool($this->entityManager);
    }

    public function createSchema()
    {
       $this->tool->createSchema($this->entityManager->getMetadataFactory()->getAllMetadata());
    }
}
?>
