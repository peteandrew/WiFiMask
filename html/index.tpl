<!DOCTYPE html>
<html>
<head><title>Esp8266 web server</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="main">
<h1>LED control</h1>
<form method="post" action="index.cgi">
<p><label for="leds">Number of LEDs</label><input id="leds" name="leds" type="text" max="50" value="%numleds%" /></p>
<p><label for="pattern">Pattern</label><input id="pattern" name="pattern" type="text" max="13" value="%pattern%" /></p>
<p><label for="red">Red</label><input id="red" name="red" type="text" max="255" value="%red%" /></p>
<p><label for="green">Green</label><input id="green" name="green" type="text" max="255" value="%green%" /></p>
<p><label for="blue">Blue</label><input id="blue" name="blue" type="text" max="255" value="%blue%" /></p>
<p><input type="submit" value="Update"></p>
</form>
</div>
</body></html>
