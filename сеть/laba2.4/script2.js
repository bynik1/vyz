dig0 = new Image(); dig0.src = "gif/dg0.gif"; dig1 = new Image(); dig1.src = "gif/dg1.gif";
dig2 = new Image(); dig2.src = "gif/dg2.gif"; dig3 = new Image(); dig3.src = "gif/dg3.gif";
dig4 = new Image(); dig4.src = "gif/dg4.gif"; dig5 = new Image(); dig5.src = "gif/dg5.gif";
dig6 = new Image(); dig6.src = "gif/dg6.gif"; dig7 = new Image(); dig7.src = "gif/dg7.gif";
dig8 = new Image(); dig8.src = "gif/dg8.gif"; dig9 = new Image(); dig9.src = "gif/dg9.gif";
dgam = new Image(); dgam.src = "gif/dgam.gif"; dgpm = new Image(); dgpm.src = "gif/dgpm.gif";
function clockTick() {
    let now = new Date();
    now.setHours(19);
    let secunde = now.getSeconds();
    let minute = now.getMinutes(); 
    let hour = now.getHours();
    hour >= 12 ? dg7.src=dgpm.src : dg7.src=dgam.src;
    hour = hour % 12;

    if (hour < 10)
        hour = "0" + hour;

    if (minute < 10)
        minute = "0" + minute;

    if (secunde < 10)
        secunde = "0" + secunde;
    
    now = null;
    // minute += "";
    // hour += "";
    // secunde += "";
    
    // if(hour<= 9){
    //     setRis(hour.charAt(1),dg1);
    //     setRis(hour.charAt(0),dg2);
    // }else{
    setRis(hour.toString().charAt(0),dg1);
    setRis(hour.toString().charAt(1),dg2);
    setRis(minute.toString().charAt(0),dg3);
    setRis(minute.toString().charAt(1),dg4);
    setRis(secunde.toString().charAt(0),dg5);
    setRis(secunde.toString().charAt(1),dg6);
    
    setTimeout("clockTick()", 1000);
    }
    
    function setRis(num,ris) {
        if (num == "0") ris.src=dig0.src;
        if (num == "1") ris.src=dig1.src;
        if (num == "2") ris.src=dig2.src;
        if (num == "3") ris.src=dig3.src;
        if (num == "4") ris.src=dig4.src;
        if (num == "5") ris.src=dig5.src;
        if (num == "6") ris.src=dig6.src;
        if (num == "7") ris.src=dig7.src;
        if (num == "8") ris.src=dig8.src;
        if (num == "9") ris.src=dig9.src;
    }
    
    clockTick();