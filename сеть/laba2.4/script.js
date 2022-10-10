let data=[];
for(i=0;i <13;i++){
    data[i]=document.getElementById('dg'+i);
}
let img = 1; 

for(i= 0; i<10; i++){
    img = new Image(); 
    img.src = "gif/dg" +i+".gif";
}
    img[11] = new Image();
    img[11].src = "gif/dgam.gif"
    img[12] = new Image();
    ing[12].src = "gif/dgpm.gif";
    
let now = new Date();

dt = [];
dt[1] = getHours(); 
dt[2] = getMinutes();
dt[3] = getDate(); 
dt[4] = getMonth();
dt[5] = getFullYear();

let time;
function displayDAte(){
    time = Math.floor(dt/10);
    data[0].src = img[time].src;
    time = dt[0]%10; 
    data[1].src=img[time].src;
}


time = Math.floor(dt[1]/10); 


setInterval(displayDate, 000);
