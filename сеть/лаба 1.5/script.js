image=document.getElementById("image");
start=document.getElementById("start");
stop=document.getElementById("stop");
fast=document.getElementById("fast");
slow=document.getElementById("slow");
let timer;
let i=1;
let sec = 200;

start.onclick = function pusk(){
    timer = setInterval(tim, sec);//Он циклически вызывает функцию или участок кода с фиксированной паузой между каждым вызовом.
    start.disabled = true;
    fast.disabled = false;
    slow.disabled = false;
    stop.disabled = false;
}

stop.onclick = function pause(){
    clearInterval(timer);//Глобальный clearInterval()метод отменяет рассчитанное по времени повторяющееся действие, которое ранее было установлено вызовом setInterval().
    start.disabled = false;
    fast.disabled = true;
    slow.disabled = true;
    stop.disabled = true;
}

fast.onclick = function faster(){
    clearInterval(timer);
    sec -= 50
    timer = setInterval(tim, sec);
}

slow.onclick = function slower(){
    clearInterval(timer);
    sec += 50
    timer = setInterval(tim, sec);
}

function tim(){
    if(i == 13){
        i = 1;
    }

    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src="gif/s"+i+".gif";
    image.src=imag.src;
    i++;
    
}
