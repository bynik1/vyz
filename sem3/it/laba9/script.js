list1=document.querySelector('.list1');
list2=document.querySelector('.list2');
list3=document.querySelector('.list3');
list4=document.querySelector('.list4');

q = document.querySelector('.q');
sum = document.querySelector('.sum');
table = document.querySelector('table');
n = 1;

function show(element){
    if(element.innerHTML == 'DeFi'){
        list1.style.display = "block";
        list2.style.display = "none";
		list3.style.display = "none";
		list4.style.display = "none";
    }
    else if(element.innerHTML == 'NFT')
    {
        list1.style.display = "none";
        list2.style.display = "block";
		list3.style.display = "none";
		list4.style.display = "none";
    }
	else if(element.innerHTML == 'Metaverse')
    {
        list1.style.display = "none";
        list2.style.display = "none";
		list3.style.display = "block";
		list4.style.display = "none";
    }
	else if(element.innerHTML == 'on the hype')
    {
        list1.style.display = "none";
        list2.style.display = "none";
		list3.style.display = "none";
		list4.style.display = "block";
    }
}

function summ(element) {
	parent = element.parentElement;
	p = parent.querySelector('p');
    h3 = parent.querySelector('h3');
	
	tr = document.createElement('tr');
	table.append(tr);
	
	td = document.createElement('td');
	td.innerHTML = n;
	tr.append(td);
	

	td = document.createElement('td');
	td.innerHTML = p.innerHTML;
	tr.append(td);
	
	td = document.createElement('td');
	td.innerHTML = h3.innerHTML;
	tr.append(td);
	
	td = document.createElement('td');
	cross = document.createElement('img');
	cross.setAttribute('src', 'gtr.jpg');
	cross.setAttribute('width', '20px');
	cross.setAttribute('onClick', 'closes(this)');
	td.append(cross);
	tr.append(td);
	
	q.innerHTML = Number(q.innerHTML) + 1;
	sum.innerHTML = Number(sum.innerHTML.replace(/[a-za-яё\s$]/gi,'')) + Number(h3.innerHTML.replace(/[a-za-яё\s$  ]/gi,''));
	sum.innerHTML += '$'
	n++;
}

chet = 0;

function openspisok() {
    if (chet == 0)
    {
        spisok = document.querySelector('.spisok');
	    spisok.style.display = "block";
        chet = 1;
    }

    else if (chet == 1)
    {
        spisok = document.querySelector('.spisok');
	    spisok.style.display = "none";
        chet = 0;
    }
	
}

function closes(element) {
	parent = element.parentElement.parentElement;
	parent.remove();
    pa = p.element;
    /*q.innerHTML = Number(q.innerHTML) - 1;*/
    /*sum.innerHTML = Number(sum.innerHTML.replace(/[a-za-яё\s]/gi,'')) - Number(h3.innerHTML.replace(/[a-za-яё\s]/gi,''));*/
   
}
