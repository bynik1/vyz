$('.menu li').mouseover(function(){
    $(this).find('ul').first().css('display', 'block');
});
 
$('.menu li').mouseout(function(){
    $(this).find('ul').first().css('display', 'none');
});