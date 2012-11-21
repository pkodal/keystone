<?php

/**
* Description of SprocketCaller
*
* @author addz
*/
class SprocketCaller
{
   /** @var array */
   private $files;

   /** @var string */
   private $outputFile;

   private $appDirectory;


   public function __construct(array $files, $outputFile, $appDirectory = NULL)
   {
       $this->files = $files;
       $this->outputFile = $outputFile;
       $this->appDirectory = $appDirectory;
   }

   public function run()
   {

       $allFiles = implode(' ', $this->files);
       exec(SPROCKETS_COMMAND . $this->getIncludeArgument() . " $allFiles", $output);
       $this->writeToFile($output);
   }

   private function getIncludeArgument()
   {
       $appArgument = '';
       if ($this->appDirectory != NULL)
       {
           $appArgument = ' -I ' . $this->appDirectory;
       }
       return $appArgument;
   }

   private function writeToFile(array $output)
   {
       $f = fopen($this->outputFile, 'w');
       if ($f)
       {
           foreach($output as $line)
           {
               fwrite($f, $line . "\n");
           }
           fclose($f);
       }
       else
       {
           throw new Exception("could not open file '$this->outputFile' to write to.");
       }
   }
}
?>