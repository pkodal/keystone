<?php

include_once(realpath(dirname(__FILE__) . '/builder/DirectorySet.inc'));
include_once(realpath(dirname(__FILE__) . '/builder/AssetSet.inc'));

include_once(realpath(dirname(__FILE__) . '/builder/DirectoryProcessor.inc'));
include_once(realpath(dirname(__FILE__) . '/builder/AssetBuilder.inc'));


/**
 * This class knows how to build all the concatenated assets for Pkodal.
 */
class PkodalAssetGenerator 
{
    const AUTO_ASSET_DIR_NAME = 'auto-assets';
    
    /** @var AssetBuilder */
    private $builder;
    
    private $fullPathToAssetDir;
    
    public function __construct() 
    {
        $this->builder = new AssetBuilder();
        $this->fullPathToAssetDir = realpath(dirname(__FILE__) . '/../../' . self::AUTO_ASSET_DIR_NAME);
    }
    
    public function run()
    {
        $this->createAssetSets();
        $this->builder->run(realpath(dirname(__FILE__) . '/../../'));
    }
    
    private function createAssetSets()
    {
        $this->createAssets('checkin', array('js'=>'pkodal-checkin.js', 'css'=>'pkodal-checkin.css'));
        $this->createAssets('framework/js/boot', array('js'=>'pkodal-jqm-boot.js'));
        $this->createAssets('framework/js/mobile', array('js' => 'pkodal-m-core.js'));
        $this->createAssets('thirdparty', array('js' => 'pkodal-3p.js'));
        $this->createAssets('homepage', array('js' => 'pkodal-appHomepage.js', 'css' => 'pkodal-appHomepage.css'), 'homepage/desktop-warning');
        $this->createAssets('homepage/desktop-warning', array('js' =>'pkodal-desktop-warning.js', 'css' => 'pkodal-desktop-warning.css'));
        $this->createAssets(array('users/profile', 'users/friends'), array('js'=> 'pkodal-profile.js', 'css' =>'pkodal-profile.css'));
        $this->createAssets('stream', array('js'=>'pkodal-stream.js', 'css' => 'pkodal-stream.css'));
        $this->createAssets('users/auth', array('js'=> 'pkodal-auth.js', 'css'=> 'pkodal-auth.css'));
        $this->createAssets('comment', array('js' => 'pkodal-comment.js', 'css' => 'pkodal-comment.css'));
        $this->createAssets('widgets', array('js' => 'pkodal-widgets.js', 'css' => 'pkodal-widgets.css'));
        $this->createAssets('thirdparty', array('js' => 'pkodal-3p.js'));
        $this->createAssets('notification', array('js' => 'pkodal-notification.js', 'css'=> 'pkodal-notification.css'));
        $this->createAssets('info', array('css' => 'pkodal-info.css'));
        $this->createAssets('search', array('js' => 'pkodal-search.js', 'css' => 'pkodal-search.css'));
        $this->createAssets('users/signup', array('js' => 'pkodal-signup.js', 'css' => 'pkodal-signup.css'), 'users/signup/whatsnext');
        $this->createAssets('users/signup/whatsnext', array('js' => 'pkodal-whatsnext.js', 'css' => 'pkodal-whatsnext.css'));
        $this->createAssets('titles', array('js' => 'pkodal-titles.js', 'css' => 'pkodal-titles.css'));
        $this->createAssets('activity', array('js' => 'pkodal-activity.js', 'css' => 'pkodal-activity.css'));
    }
    
    private function createAssets($dirName, array $assets, $exludeDir = NULL)
    {
        $dirs = new DirectorySet();
                
        if (is_array($dirName))
        {
            foreach ($dirName as $name)
            {
                $dirs->addDirectory($name);
            }
        }
        else
        {
            $dirs->addDirectory($dirName);
        }
        
        if (isset($exludeDir))
        {
            $dirs->excludeDirectory($exludeDir);
        }
        
        $assets = new AssetSet($dirs, $this->getPath('js', $assets), $this->getPath('css', $assets));
        $this->builder->addAssetSet($assets);
    }
    
    private function getPath($type, $assets)
    {
        if (array_key_exists($type, $assets) && isset($assets[$type]))
        {
            return $this->fullPath($assets[$type]);
        }
        return NULL;
    }
    
    private function fullPath($filename)
    {
        return $this->fullPathToAssetDir . '/' . $filename;
    }
}

?>
