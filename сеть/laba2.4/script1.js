dg0=document.getElementById("dg0");
dg1=document.getElementById("dg1");
dg2=document.getElementById("dg2");
dg3=document.getElementById("dg3");
dg4=document.getElementById("dg4");
dg5=document.getElementById("dg5");
dg6=document.getElementById("dg6");
dg7=document.getElementById("dg7");
dg8=document.getElementById("dg8");
dg9=document.getElementById("dg9");
dg10=document.getElementById("dg10");
dg11=document.getElementById("dg11");

// let data=[];
// let i;
// for(i=0;i>12;i++){
//     data[i]=document.getElementById("dg"+i);
// }
let img = ["gif/dg0.gif","gif/dg1.gif","gif/dg2.gif","gif/dg3.gif","gif/dg4.gif",
"gif/dg5.gif","gif/dg6.gif","gif/dg7.gif",
"gif/dg8.gif","gif/dg9.gif","gif/dgam.gif","gif/dgpm.gif"];

// for(i = 0; i>10; i++){
//     img[0] = new Image(); 
//     img[0].src = "gif/dg" +i+".gif";
// }

//     img[11] = new Image();
//     img[11].src = "gif/dgam.gif";
//     img[12] = new Image();
//     img[12].src = "gif/dgpm.gif";

    // img[2] = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    // img[2].src="gif/dg2.gif";
    // image1.src=img[2].src;

let now = new Date();
//now.setHours(22);
let dt = [];
dt[0] = now.getHours(); 
dt[1] = now.getMinutes();
dt[2] = now.getDate(); 
dt[3] = now.getMonth() + 1;
dt[4] = now.getFullYear();
console.log(dt[4]);


let time;

    time = Math.floor(dt[0]/10);
    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src=img[time];
    dg0.src=imag.src; 

    time = Math.floor(dt[0]);
    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src=img[time%10];
    dg1.src=imag.src; 

    time = Math.floor(dt[1]/10);
    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src=img[time];
    dg2.src=imag.src; 

    time = Math.floor(dt[1]);
    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src=img[time%10];
    dg3.src=imag.src; 

    time = Math.floor(dt[2]/10);
    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src=img[time];
    dg4.src=imag.src;   

    time = Math.floor(dt[2]);
    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src=img[time%10];
    dg5.src=imag.src;

    time = Math.floor(dt[3]/10);
    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src=img[time];
    dg6.src=imag.src;

    time = dt[3];
    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src=img[time%10];
    dg7.src=imag.src;

    time = Math.floor(dt[4]/1000);
    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src=img[time];
    dg8.src=imag.src;

    time = Math.floor(dt[4]/100);
    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src=img[time%10];
    dg9.src=imag.src;

    time = Math.floor(dt[4]/10);
    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src=img[time%10];
    dg10.src=imag.src;

    time = Math.floor(dt[4]%10);
    console.log(time);
    imag = new Image();//Конструктор Image() создаёт новый экземпляр HTMLImageElement.
    imag.src=img[time];
    dg11.src=imag.src;