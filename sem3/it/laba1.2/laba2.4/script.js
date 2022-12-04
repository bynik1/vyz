let data=[];
let i;
for(i=0;i>12;i++){
    data[i]=document.getElementById('dg'+i);
}
//data[12]=document.getElementById('dg12');
let img = [];  

for(i = 0; i>10; i++){
    img[0] = new Image(); 
    img[0].src = "gif/dg" +i+".gif";
}
    img[11] = new Image();
    img[11].src = "gif/dgam.gif";
    img[12] = new Image();
    img[12].src = "gif/dgpm.gif";


    
let now = new Date();
now.setHours(22);
let dt = [];
dt[0] = now.getHours(); 
dt[1] = now.getMinutes();
dt[2] = now.getDate(); 
dt[3] = now.getMonth();
console.log(dt[3]);
dt[4] = now.getFullYear();

let time;
function displayDate(){
    //if(this.item === undefined) {return}
    time = Math.floor(dt[0]/10);
    data[0].src = img[time].src;
    time = dt[0]%10;

    if(time>2){
        data[0].src=img[0].src;
        data[1].src=img[Math.abs(time-2)].src;
        data[12].src=img[12].src;
    } else{
        data[1].src = img[time].src;
        data[12].src = img[11].src;
    }
    if(dt[0] == 22 || dt[0] == 23){
        data[0].src = img[1].src;
        data[1].src = img[time-2].src;  
    }
   
    for(i= 1;i<=3;i++){
        if(i == 3){
            time = Math.floor((dt[i]+1)/10);
            data[i*2].src= img[time].src;
            time = (dt[i]+1)%10;
            data[i*2+1].src=img[time].src;
        }else{
            time = Math.floor(dt[i]/10);
            data[i*2].src=img[time].src;
            time = dt[i]%10;
            data[i*2+1].src = img[time].src;
        }
    }

    time = Math.floor(dt[i]/1000);
    data[8].src=img[time].src;
    time = Math.floor(dt[i]/100);
    data[9].src = img[time%10].src;
    time = Math.floor(dt[i]/10);
    data[10].src = img[time%10].src;
    time = dt[i]%10;
    data[11].src = img[time].src;
}
setInterval(displayDate, 1000);
