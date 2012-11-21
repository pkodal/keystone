<?php

/**
 * Process a set of directories from a given root location recursively.
 * In-order recursive traversal.
 */
abstract class DirectoryProcessor 
{
    public function run($rootDirectory)
    {
        $dirs = glob("$rootDirectory/*", GLOB_ONLYDIR);
        $this->visitDir($dirs);
    }
    
    private function visitDir($dirStack)
    {
        while (count($dirStack) > 0)
        {
            $dir = array_pop($dirStack);

            $this->processDir($dir);

            $newDirs = glob("$dir/*", GLOB_ONLYDIR);
            $this->visitDir($newDirs);
        }
    }
    
    /**
     * Process a directory.
     * @param $directoryName the directory to process
     */
    protected abstract function processDir($directoryName);
}

?>
