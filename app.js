let gameseq=[];
let userseq=[];

let btns=["purple","green","red","yellow"];

let started=false;
let level=0;

let h2=document.querySelector("h2");
 
document.addEventListener("keypress",function() {
    if (started==false) {
        console.log("Game started");
        started=true;

        levelup();
    }
 });

  function gameFlash(btn){
    btn.classList.add("flash");
    setTimeout(function(){
        btn.classList.remove("flash");
    },250);
 }

  function userFlash(btn){
    btn.classList.add("userFlash");
    setTimeout(function(){
        btn.classList.remove("userFlash");
    },250);
 }
function  levelup() {
    level++;
    h2.innerText=`Level ${level}`;

    let randIdx = Math.floor(Math.random()*3);
    let randColor=btns[randIdx];
    let randBtn = document.querySelector(`.${randColor}`);
    gameseq.push(randColor);
    console.log(gameseq);
    gameFlash(randBtn);
}
function check(idx) {
    if (userseq[idx]===gameseq[idx]){
        if (userseq.length===gameseq.length){
                setTimeout(levelup,1000); 
        }
    }else{
    console.log("wrong value");
    h2.innerText=`Game Over, Press Any Key to Restart`;
}
}
function btnPress(){
    console.log(this);
    let btn=this;
    userFlash(btn);

usercolor=btn.getAttribute("id");
userseq.push(usercolor);
 check(userseq.length-1);
}

let allBtns =document.querySelectorAll(".btn");
for (btn of allBtns){
    btn.addEventListener("click",btnPress);
}




