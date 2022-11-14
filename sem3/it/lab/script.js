var timer;
var lasttarget;

for (var i = 0; i < 3; i++) {

    var menu = document.getElementsByClassName("menu")[i];
    var sub = menu.getElementsByClassName("subMenu")[0];
    var headline = menu.getElementsByClassName("headline")[0];

    headline.onmouseover = function () {
        var target = event.target;//цель наведения
        var menu_ref = target.parentNode;//
        var sub_ref = menu_ref.getElementsByClassName("subMenu")[0];
        target.style.backgroundColor = "lightblue";//меняет цвет
        sub_ref.style.display = "";//прекратить отображать
        //console.log(target);
        //console.log(lasttarget);
        if (target == lasttarget) // если на текущий headline навестись, то clearTimeout не позволит скрыть подменю 
            clearTimeout(timer);
    };

    headline.onmouseout = function () {
        lasttarget = event.target; // хранит последний уведенный headline
        var target = event.target;
        var menu_ref = target.parentNode;
        var sub_ref = menu_ref.getElementsByClassName("subMenu")[0];
        timer = setTimeout(hide, 1, target, sub_ref);
    };

    sub.onmouseover = function () {
        clearTimeout(timer);
        var target = event.target;
        target.style.backgroundColor = "lightblue";

    };

    sub.onmouseout = function () {
        var sub_ref = event.currentTarget;
        var target = event.target;
        target.style.backgroundColor = "";
        target = sub_ref.parentNode.getElementsByClassName("headline")[0];
        timer = setTimeout(hide, 1, target, sub_ref);

    };

}

function hide(target, sub_ref) {

    target.style.backgroundColor = "";
    target.style.color = "";
    sub_ref.style.display = "none";
}