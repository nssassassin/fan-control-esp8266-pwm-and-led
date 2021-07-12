const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
.card{
    max-width: 400px;
     min-height: 250px;
     background: #02b875;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
.row {
  display: flex;
  flex-wrap: wrap;
  padding: 0 4px;
}

/* Create four equal columns that sits next to each other */
.column {
  flex: 25%;
  max-width: 25%;
  padding: 0 4px;
}
</style>
<body>
<div class="row">

  <div class="column">
    <div class="card">
       <h1>PWM Fan 1</h1><br>
       <h1>Sensor Value:<span id="PWM1">0</span></h1><br>
    </div>
    <div class="card">
      <h1>PWM Fan 2</h1><br>
      <h1>Sensor Value:<span id="PWM2">00</span></h1><br>
    </div>
  </div>

  <div class="column">
    <div class="card">
      <h1>PWM Fan 3</h1><br>
    <h1>Sensor Value:<span id="PWM3">000</span></h1><br>
    </div>
    <div class="card">
     <h1>PWM Fan 4</h1><br>
     <h1>Sensor Value:<span id="PWM4">0000</span></h1><br>
    </div>
  </div>
  <div class="column">
    <div class="card">
      <h1>PWM Fan 5</h1><br>
      <h1>Sensor Value:<span id="PWM5">00000</span></h1><br>
    </div> 
    <div class="card">
      <h1>PWM Fan 6</h1><br>
     <h1>Sensor Value:<span id="PWM6">00000</span></h1><br>
    </div>
  </div>
</div>
<script>

setInterval(function() {
  // Call a function repetatively with 1 Second interval
  getData();
}, 1000); //1000mSeconds update rate

function getData() {
  
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("PWM1").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "getPWM1", true);
    xhttp.send();
    
    xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("PWM2").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "getPWM2", true);
    xhttp.send();

    xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("PWM3").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "getPWM3", true);
    xhttp.send();
    xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("PWM4").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "getPWM4", true);
    xhttp.send();
    xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("PWM5").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "getPWM5", true);
    xhttp.send();

    xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("PWM6").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "getPWM6", true);
    xhttp.send();
  

}
</script>
</body>
</html>
)=====";