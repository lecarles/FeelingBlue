
	var slider = document.getElementById("myRange");
	var output = document.getElementById("demo");

	//setup function
	window.onload = function(){
		slider.value = 0 ;
		document.body.style.backgroundColor = `hsl(${slider.value},65%,60%)`;
	}

	//
	slider.oninput = function() {
	  var value = 360 - this.value;
	  document.body.style.backgroundColor = `hsl(${value},65%,60%)`;

	}

	slider.onmouseup = function() {
	  var xhr = new XMLHttpRequest();
		xhr.open('GET', `http://192.168.0.101/hand3/${this.value}`);
		//if (Math.random()>0.5) xhr.open('GET', `http://192.168.1.113/gpio/0`);
		//else xhr.open('GET', `http://192.168.1.113/gpio/1`);
		xhr.send();
	}


	slider.ontouchend = function() {
	  var xhr = new XMLHttpRequest();
		xhr.open('GET', `http://192.168.0.101/hand2/${this.value}`);
		//if (Math.random()>0.5) xhr.open('GET', `http://192.168.1.113/gpio/0`);
		//else xhr.open('GET', `http://192.168.1.113/gpio/1`);
		xhr.send();
	}
	

	


