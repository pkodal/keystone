<?php
include_once(realpath(dirname(__FILE__) . '/PasswordGenerator.inc'));

/**
 * @Entity
 * @Table(name="users")
 */
class User
{
    const MAX_BIO_LEN = 144;
    
    /**
     * @Id
     * @Column(type="bigint")
     * @generatedValue(strategy="AUTO")
     */
    private $id;
    
    /**
     * @Column(type="string", length=32)
     */
    private $firstname;

    /**
     * @Column(type="string", length=32)
     */
    private $lastname;

    /**
     * @Column(type="string")
     * @var string
     */
    private $password;
    
    /**
     * @Column(type="string")
     * @var string
     */
    private $pictureUrl;
    
    /**
     * @Column(type="string", length=144, nullable=true)
     * @var string 
     */
    private $bio;
    


    public function __construct()
    {
        $this->id = NULL;
        $this->firstname = NULL;
        $this->lastname = NULL;
        $this->email = NULL;
        $this->password = NULL;
        $this->bio = NULL;
    }
    
    public function recordActivity(UserAction $activity, $source = NULL)
    {
        if (!isset($this->activityCenter))
        {
            $this->activityCenter = Registry::getRegistry()->fetch(ACTIVITY_CENTER);
        }
        $this->activityCenter->record($this, $activity, $source);
    }
    
    
   
    public function getId()
    {
        return $this->id;
    }

    public function setFirstName($firstname)
    {
        $this->firstname = $firstname;
    }

    public function getFirstName()
    {
        return $this->firstname;
    }

    public function setLastName($lastname)
    {
        $this->lastname = $lastname;
    }

    public function getLastName()
    {
        return $this->lastname;
    }

    public function toArray()
    {
        return array('id' => $this->id,
                     'firstname' => $this->firstname,
                     'lastname' => $this->lastname,
                     'picture'=> $this->pictureUrl,
               );
    }

    public function toJson()
    {
        return json_encode($this->toArray());
    }

    public function setEmail($email)
    {
        $this->email = $email;
    }

    public function getEmail()
    {
        return $this->email;
    }
    
    public function getBio()
    {
        return $this->bio;
    }
    
    public function setBio($bio)
    {
        if (strlen($bio) > self::MAX_BIO_LEN)
        {
            throw new Exception('Bio too long');
        }
        
        if ($bio == '')
        {
            $bio = NULL;
        }
        
        $this->bio = HtmlUtil::escapeString($bio);
    }
    
    public function getPassword()
    {
        return $this->password;
    }
    
    public function setPassword($password)
    {
        $this->password = PasswordGenerator::create($password);
    }
    
    public function setPictureUrl($url)
    {
        $this->pictureUrl = $url;
    }

    public function getPictureUrl()
    {
        return $this->pictureUrl;
    }
}

?>