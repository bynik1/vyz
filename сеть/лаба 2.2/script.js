image1=document.getElementById("image1");
image2=document.getElementById("image2");
start=document.getElementById("start");
stop=document.getElementById("stop");
fast=document.getElementById("fast");
slow=document.getElementById("slow");
let timer;
let i=1, b=0;
let sec = 200;

start.onclick = function pusk(){
    timer = setInterval(tim, sec);//Он циклически вызывает функцию или участок кода с фиксированной паузой между каждым вызовом.
    start.disabled = false;
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
    if(b == 0){
        imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
        imag.src="gif/s"+i+".gif";
        image1.src=imag.src;
        if(i == 12){
            i = 0;
            b = 1;
            imag.src="gif/s"+8+".gif";
            image1.src=imag.src;
        }
        i++;
    }

    if(b == 1){
        imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
        imag.src="gif/s"+i+".gif";
        image2.src=imag.src;
        if(i == 12){
            i = 0;
            b = 0;
            imag.src="gif/s"+8+".gif";
            image2.src=imag.src;
        }
        i++;
    }
    


    
    
}
