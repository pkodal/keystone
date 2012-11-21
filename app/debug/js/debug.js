
function Debug()
{

    this.bindDebugTools = function()
    {
        $('.debug-info a').click(toggleDebugMenu);
        $('.debug-menu-close').click(toggleDebugMenu);
        $('.debug-console-close').click(closeDebugConsole);

        $('#debug-subscribed-events').click(subcribedTopics);
        $('#debug-timers').click(activeTimers);
        $('#debug-logging').click(logging)
    }

    function toggleDebugMenu()
    {
        $('.debug-menu').toggle();
        $('.debug-info a').toggleClass('debug-menu-open');
    }

    function logging()
    {
        var isEnabled = Framework.isConsoleLoggingOn();

        var content = 'Console logging:<br/><a id="logging-on-button">On</a>&nbsp;|&nbsp;<a id="logging-off-button">Off</a>';
        
        setDebugConsoleContent(content);
        bindLoggingButtons();
        initLoggingButtons(isEnabled);

        showDebugConsole();
    }
    
    function initLoggingButtons(isLoggingEnabled)
    {
        if (isLoggingEnabled)
        {
            $('#logging-on-button').addClass('selected');
            $('#logging-off-button').removeClass('selected');
        }
        else
        {
            $('#logging-on-button').removeClass('selected');
            $('#logging-off-button').addClass('selected');
        }
    }

    function bindLoggingButtons()
    {
        $('#logging-on-button').click(function() {
           loggingButtonClick(true); 
        });
        $('#logging-off-button').click(function() {
            loggingButtonClick(false);
        });
    }

    function loggingButtonClick(enableLogging)
    {
        if (!enableLogging)
        {
            Framework.log('Console logging disabled through debug.');
        }

        Framework.setConsoleLogging(enableLogging);
        initLoggingButtons(enableLogging);

        if (enableLogging)
        {
            Framework.log('Console logging enabled through debug.');
        }
    }

    function subcribedTopics()
    {
        var subs  = Framework.getSubscribers();

        if (sizeOfAssociativeArray(subs) > 0)
        {
            var content = "<br/><table><tr><th>Event topic</th><th>registered functions</th></tr>";
            for (var i in subs)
            {
                content += '<tr><td><a class="debug-subs-link">' + i + '</a></td><td>' + subs[i] + '</td></tr>';
            }
            content += "</table><br/>";

            content += 'Fire event: <input type="text" id="debug-fire-event"/><a id="debug-notify-button">notify</a><br/>';
            setDebugConsoleContent(content);
            $("#debug-notify-button").click(debugNotifyButton);
        }
        else
        {
            setDebugConsoleContent("<br/><p>No event topics subscribed.</p><br/>");
        }

        bindTopicButtons();
        showDebugConsole(content);
    }

    function bindTopicButtons()
    {
        $(".debug-subs-link").click(function() {
            $('#debug-fire-event').val($(this).html());
        });
    }

    function debugNotifyButton()
    {
        var topic = $('#debug-fire-event').val();
        Framework.notify(topic);
    }


    function activeTimers()
    {
        var timers = Framework.getTimers();

        var content = "<br/><p>No timer objects in use.</p><br/>";

        if (sizeOfAssociativeArray(timers) > 0)
        {

            content = "<br/><table><tr><th>Timer name</th><th>timer object</th></tr>";
            for (var i in timers)
            {
                content += '<tr><td>' + i + '</td><td>' + timers[i] + '</td></tr>';
            }
            content += "</table><br/>";
        }

        setDebugConsoleContent(content);
        showDebugConsole();
    }

    function sizeOfAssociativeArray(array)
    {
        var size = 0;
        for (var i in array)
        {
            size++;
        }
        return size;
    }

    function setDebugConsoleContent(htmlContent)
    {
        $('.debug-console-inner').html(htmlContent);
    }

    function showDebugConsole()
    {
        $('.debug-console').show();
    }

    function closeDebugConsole()
    {
        $('.debug-console').hide();
    }

}

jQuery(document).ready(function()
{
    var debug = new Debug();
    debug.bindDebugTools();
});