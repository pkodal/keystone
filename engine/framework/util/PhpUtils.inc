<?php

function parseStringtoBoolean($string)
{
    if (strtolower($string) === "true")
    {
        return true;
    }
    else if (strtolower($string) === "false")
    {
        return false;
    }
    
    throw new Exception("Invalid type only true and false accepted");
}

function parseBooleanToString($bValue = false) 
{                      // returns string
  return ($bValue ? 'true' : 'false');
}

function safeFieldCopy($fieldName, $fromArray, &$toArray, $minSize = 1, $maxSize = 30)
{
    if (array_key_exists($fieldName, $fromArray) &&
        count($fromArray[$fieldName]) >= $minSize &&
        count($fromArray[$fieldName]) <= $maxSize)
    {
        $toArray[$fieldName] = $fromArray[$fieldName];
    }
    else
    {
        throw new Exception("Could not read from field $fieldName");
    }
}

/**
 * @param string $filename filename relative to asset DIR
 */
function assetFile($filename)
{
    return assetDirName() . '/' . assetFileName($filename);
}

/**
 * @return string asset directory name.
 */
function assetDirName()
{
    if (AUTOLOAD_ASSETS)
    {
        return 'auto-assets';
    }
    
    return 'assets';
}

function assetFileName($filename)
{
    if (AUTOLOAD_ASSETS)
    {
        return $filename;
    }
    
    $file =  strtok($filename, '.');
    $ext = strtok('.');
    
    return $file . '-' . VERSION . ".$ext";
}


function getBaseDomain($domainb)
{
    if (strpos($domainb, 'localhost') !== false)
    {
        return 'localhost';
    }
    
    if (preg_match('/\d+.\d+.\d+.\d+/', $domainb))
    {
        return $domainb;
    }
    
    $bits = explode('/', $domainb);
    
    if ($bits[0]=='http:' || $bits[0]=='https:') 
    { 
        $domainb= $bits[2]; 
    }
    else 
    { 
        $domainb= $bits[0]; 
    }
    
    unset($bits); 
    $bits = explode('.', $domainb); 
    $idz=count($bits); 
    $idz-=3; 
    
    if (strlen($bits[($idz+2)])==2) 
    { 
        $url=$bits[$idz].'.'.$bits[($idz+1)].'.'.$bits[($idz+2)]; 
    } 
    else if (strlen($bits[($idz+2)])==0) 
    { 
        $url=$bits[($idz)].'.'.$bits[($idz+1)]; 
    } 
    else 
    { 
        $url=$bits[($idz+1)].'.'.$bits[($idz+2)]; 
    }
    return $url; 
}

?>
