
	var slider = document.getElementById("myRange");
	var output = document.getElementById("demo");

	//setup function
	window.onload = function(){
		slider.value = Math.random() * 359 ;
		document.body.style.backgroundColor = `hsl(${slider.value},65%,60%)`;
	}

	//
	slider.oninput = function() {
	  document.body.style.backgroundColor = `hsl(${this.value},65%,60%)`;

	}

	


