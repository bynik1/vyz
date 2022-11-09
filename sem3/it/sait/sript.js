q = document.querySelector('#q');
sum = document.querySelector('.sum');
list1 = document.querySelector('.list1');
list2 = document.querySelector('.list2');
function summ(element){

    tr = document.createElement('tr');// создание строчки
    table.append(tr);//добавление строчки в таблицу

    td = document.createElement('td');// создание строчки
    td.innerHTML = n;//добавление строчки в таблицу
    tr.append(td);

    td = document.createElement('td');// создание строчки
    td.innerHTML = p[0].innerHTML;//добавление строчки в таблицу
    tr.append(td);

    td = document.createElement('td');// создание строчки
    td.innerHTML = p[1].innerHTML;//добавление строчки в таблицу
    tr.append(td);

    td = document.createElement('td');
    cross = document.createElement('img');
    cross.setAttribute('src', 'img/cross.png');
    cross.setAttribute('width', '20px');
    cross.setAttribute('onclick', 'closes(this)');
    td.append(cross);
    tr.append(td);

    parent = element.parentElement();//родитель наше    й кнопки
    p = parnet.querySelectorAll('p');
    q.innerHTML = Number(q.innerHTML) + 1;
    sum.innerHTML = Number(sum.innerHTML.replace(/[a-zа-яё\s]/gi,""))+ Number(p[1].innerHTML.replace(/[a-zа-яё\s]/gi,""));
    sum.innerHTML +='.p';

}

function show(element){
    if(element.innerHTML == "RTX 3070 Ti"){
        list1.style.display = "block";
        list2.style.display = "none";
    }else if(element.innerHTML == "RTX 3060 Ti"){
        list2.style.display = "block";
        list1.style.display = "none";
    }
}

function openspis(){
    spisok = document.querySelector('.spisok');
    spisok.stype.display = "block";
}

function closes(element){
    parent = element.parentElement.parentElement;
    parent.remove();
}