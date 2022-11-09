<html>
<head>
<title>Перестановка двух изображений</title>
<script>
function chpict(){
 var l = document.pm1.src
 document.pm1.src = document.pm2.src
 document.pm2.src = l
}
</script>
< !--   
</head>
<body>
<img src="1.jpg" name="pm1">
<img src="index.jpg" name="pm2">
<form name="form1">
 <input type="button" value="Обновить" onClick="chpict()">
</form>
//-->
</body>
</html>