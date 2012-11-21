<?php

function registerFrameworkExceptionHandler()
{
    // TODO: do we need to do this on every request? can we set once some how?
    set_exception_handler('frameworkUncaughtExceptionHandler');
}

/**
 * @param Exception $exception to send.
 */
function frameworkUncaughtExceptionHandler($exception)
{
    // framework exceptions are always dispatched to the site-level error handler.
    if (is_a($exception, 'FrameworkException'))
    {
        $dispatcher = Registry::getRegistry()->fetch(DISPATCHER_ID);
        $dispatcher->dispatchToErrorHandler("Framework Exception: " . $exception->getMessage());
        return;
    }
    setNoCacheHeaders();
    // TODO eventually provide the ability for app defined, custom formatters.
    sendResource(FrameworkExceptionFormatter::formatException($exception));
}

class FrameworkExceptionFormatter
{
    /**
     * @param Exception $exception to format.
     * @return Resource
     */
    public static function formatException($exception)
    {
        if (is_a($exception, 'Resource'))
        {
            return $exception;
        }

        if (isJsonType())
        {
            return self::formatJsonResource($exception);
        }

        return self::formatHtmlResource($exception);
    }

    private static function formatJsonResource(Exception $exception)
    {
        $jsonArray = array(
                        JsonResource::SUCCESS_FIELD_NAME => false,
                        JsonResource::DATA_FIELD_NAME =>$exception->getMessage(),
                        'code' => $exception->getCode());

        if (VERBOSE_EXCEPTIONS)
        {
            $jsonArray['VERBOSE'] = self::formatHtmlMessage($exception);
        }


        return new JsonResource($jsonArray);
    }

    private static function formatHtmlResource($exception)
    {
        return new WidgetResource('<div class="exception"><p class="code">' . $exception->getCode() .
                        '</p><p class="message">' . self::formatHtmlMessage($exception) . '</p></div>');
    }

    /**
     * @param Exception $exception
     * @return string
     */
    private static function formatHtmlMessage($exception)
    {
        $message;

        if (VERBOSE_EXCEPTIONS)
        {
            return self::formatVerboseMessage($exception);
        }

        return $exception->getMessage();
    }
    
    private static function formatVerboseMessage($exception)
    {
        return "<b>" . $exception->getMessage() . "</b>" .
                "<br/>File: " . $exception->getFile()  .
                ", line: " . $exception->getLine() .
                "<br/>" . $exception->getTraceAsString();

    }
}


?>
