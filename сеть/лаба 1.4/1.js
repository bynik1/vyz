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
</head>
<body>
<img src="m1.gif" name="pm1">
<img src="m2.gif" name="pm2">
<form name="form1">
 <input type="button" value="Обновить" onClick="chpict()">
</form>
</body>
</html>