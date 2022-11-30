count=document.getElementById("count");
price_rub=document.getElementById("price_rub");
price_usdt=document.getElementById("price_usdt");



function maticrub(){
    price_rub.value = count.value * 0.8*65;
    setTimeout(maticusdt, 0);
}

function maticusdt(){
    price_usdt.value = count.value * 0.8;
}

function bnbrub(){
    price_rub.value = count.value * 300*65;
    setTimeout(bnbusdt, 0);
}

function bnbusdt(){
    price_usdt.value = count.value * 300;
}

function avaxrub(){
    price_rub.value = count.value * 16*65;
    setTimeout(avaxusdt, 0);
}

function avaxusdt(){
    price_usdt.value = count.value * 16;
}

function solrub(){
    price_rub.value = count.value * 14*65;
    setTimeout(solusdt, 0);
}

function solusdt(){
    price_usdt.value = count.value * 14;
}