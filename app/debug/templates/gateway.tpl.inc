<html>
<head>
    <title>Site Debug</title>
</head>
<body>
    <div class="debug-info debug-overlay">
        Debug Gateway - viewing module path: <?=$modulePath?><a>Tools <img alt="" src="/debug/img/down-arrow.png"></a>
    </div>
    <div class="debug-menu debug-overlay" style="display: none;">
         <!-- TODO all this can be made generic to insert a whole bunch of different tools. -->
        <span>Debug tools <a class="debug-menu-close">[x]</a></span>
        <ul>
            <li><a id="debug-subscribed-events">Subscribed events</a></li>
            <li><a id="debug-timers">Scheduled Timers</a></li>
            <li><a id="debug-logging">Javascript logging</a></li>
        </ul>
    </div>
    <div class="debug-console debug-overlay" style="display: none">
        <div class="debug-overlay-title"><span>Debug console</span><a class="debug-console-close">[x]</a></div>
        <div class="debug-console-inner"></div>
    </div>

    <div class="main-container">
        <div class="main main-content">
            <?=$moduleContent?>
            <?=$headerScriptIncludes?>
            <?=$headerCssIncludes?>
        </div>
    </div>
</body>
</html>