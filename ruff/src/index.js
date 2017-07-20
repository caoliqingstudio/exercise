'use strict';
var http = require('http');
var feeling = 100;
var address = '139.198.15.144';

var buttonFlag = 0;
var buttonArray = [];
var buttonLength = 4;

var soundState=0;
//HTTP请求
function postState(state) {
  var options = {
    host: address,
    port: '80',
    path: '/api/sensor',
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Content-Length': JSON.stringify(state).length
    }
  };
  var req = http.request(options, function(response) {
	  response.on('data', function (chunk) {
            console.log('BODY: ' + chunk);
        });
  });

  req.write(JSON.stringify(state));

  req.end();
}
function postButton(state) {
  var options = {
    host: address,
    port: '80',
    path: '/api/button',
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Content-Length': JSON.stringify(state).length
    }
  };
  var req = http.request(options, function(response) {
	  response.on('data', function (chunk) {
            console.log('BODY: ' + chunk);
			feeling=(parseInt(chunk)==='NaN')?feeling:parseInt(chunk);
			console.log('feeling',feeling);
        });
  });

  req.write(JSON.stringify(state));

  req.end();
}
function showSound(nowFeeling) {
//  var sound, x;
  if (nowFeeling > 90) {
    //sound = [1, 0, 1, 0, 1, 0, 1, 0];
  } else if (nowFeeling > 60) {
    //sound = [1, 1, 0, 1, 1, 0, 1, 0];
  } else {
	if(soundState=0){
		$('#fc-49').turnOn(function(error) {
			if (error) {
				console.error(error);
				return;
			}
		});
		++soundState;
	}else if(soundState=5){
		soundState=0;
	}else{
		$('#fc-49').turnOff(function(error) {
			if (error) {
				console.error(error);
				return;
			}
		});			
	}
    //sound = [1, 1, 1, 1, 1, 1, 1, 0];
  }
/*  for (x in sound) {
    if (sound[x] > 0) {
        $('#fc-49').turnOn(function(error) {
          if (error) {
            console.error(error);
            return;
          }
		});
	}
	for(var i=0;i==-1;i++);
    $('#fc-49').turnOff(function(error) {
		if (error) {
			console.error(error);
			return;
		}
    });
  }*/
}

function showFeeling(nowFeeling) {
  var showColor;
  if (nowFeeling > 90) {
    showColor = [0x90, 0x01, 0x01];
  } else if (nowFeeling > 60) {
    showColor = [0x01, 0x80, 0x01];
  } else {
    showColor = [0x01, 0x01, 0xC0];
  }
  $('#led').setRGB(showColor);
  //showSound(nowFeeling);
}

$.ready(function(error) {
  if (error) {
    console.log(error);
    return;
  }
  var nowtemperature,nowhumidity,nowgyvalue,nowsound;

  setInterval(function() {
    console.log('post');
	showSound(feeling);
	//var nowtemperature,nowhumidity,nowgyvalue,nowsound;
	nowsound=0;
	$('#dht11').getTemperature(function(error,temperature){
		if(error){
			console.error(error);
			return;
		}
		nowtemperature=temperature;
	});//获取温度	
	$('#dht11').getRelativeHumidity(function(error,humidity){
		if(error){
			console.error(error);
			return;
		}
		nowhumidity=humidity;
	});//获取湿度
	$('#gy-30').getIlluminance(function (error, gyvalue) {
		if (error) {
			console.error(error);
			return;
		}
		nowgyvalue=gyvalue;
	});

	$('#sound-01').on('sound',function(){
		nowsound=1;
	});
    var temp1 = {
      'sensor':'temperature',
	  'data':nowtemperature
    };
	var temp2 = {
      'sensor':'humidity',
	  'data':nowhumidity
    };
	var temp3 = {
      'sensor':'light',
	  'data':nowgyvalue
    };
	var temp4 = {
      'sensor':'voice',
	  'data':nowsound
    };
    postState(temp1);
    postState(temp2);
    postState(temp3);
    postState(temp4);
	showFeeling(feeling);
  }, 20000);
  //大按钮
  $('#button1').on('push', function(){
    // var temp = {
    //   'red': 1,
    //   'blue': 0
    // };
	if (buttonFlag < buttonLength){
      var btn = 1;
      buttonArray.push(btn);
      buttonFlag ++;
		console.log('Buttonred pushed.');
      if(buttonFlag == buttonLength){
        buttonFlag = 0;
		var temp={
		  'data':buttonArray[0]*1000+buttonArray[1]*100+buttonArray[2]*10+buttonArray[3]
		};
		console.log(temp);
		postButton(temp);
		buttonArray.splice(0,4);
      };
    };
    // showFeeling(feeling);
  }); //红色 

  $('#but3').on('push', function(){
	console.log('Buttonblue pushed.');
    if (buttonFlag < buttonLength){
      var btn = 0;
      console.log('Buttonred pushed.');
	  buttonArray.push(btn);
      buttonFlag ++;
      if(buttonFlag == buttonLength){
        buttonFlag = 0;
		var temp={
		  'data':buttonArray[0]*1000+buttonArray[1]*100+buttonArray[2]*10+buttonArray[3]
		};
		console.log(temp);
		postButton(temp);
		buttonArray.splice(0,4);
      };
    };
  }); //蓝色*/
});
/*
$.ready(function(error) {
  if (error) {
    console.log(error);
    return;
  }

    setInterval(function() {

    var nowtemperature, nowhumidity, nowgyvalue, nowsound;
    nowsound = 0;

    $('#dht11').getTemperature(function(error, temperature) {
      if (error) {
        console.error(error);
        return;
      }
      nowtemperature = temperature;
    }); //获取温度
    $('#dht11').getRelativeHumidity(function(error, humidity) {
      if (error) {
        console.error(error);
        return;
      }
      nowhumidity = humidity;
    }); //获取湿度

    $('#gy-30').getIlluminance(function(error, gyvalue) {
      if (error) {
        console.error(error);
        return;
      }
      nowgyvalue = gyvalue;
    });

    $('#sound-01').on('sound', function() {
      nowsound = 1;
    });

    console.log('post');

    var temp = {
      'temperature': nowtemperature,
      'humidity': nowhumidity,
      'light': nowgyvalue,
      'voice': nowsound
    }

    postState(temp);
    console.log(temp);
  }, 3000);
  $('#button1').on('push', function () {
	 var temp = {
		 'red':1,
		 'blue':0
	 };
//	 postState(temp);
	 console.log(temp);//for test
	 showFeeling(feeling);
  });//红色
  $('#button2').on('push', function () {
	 var temp = {
		 'red':0,
		 'blue':1
	 };
//	 postState(temp);
	 console.log(temp);//for test
	 showFeeling(feeling);
  });//蓝色
/*  //大按钮
  $('#button1').on('push', function(){
    // var temp = {
    //   'red': 1,
    //   'blue': 0
    // };
	if (buttonFlag < buttonLength){
      var btn = '1';
      buttonArray.push(btn);
      buttonFlag ++;
		console.log('Buttonred pushed.');
      if(buttonFlag == buttonLength){
        buttonFlag = 0;
        console.log('butten',buttonArray);
		buttonArray.splice(0,4);
      };
    };
    // showFeeling(feeling);
  }); //红色

  $('#button2').on('push', function(){
	console.log('Buttonblue pushed.');
    if (buttonFlag < buttonLength){
      var btn = '0';
      console.log('Buttonred pushed.');
	  buttonArray.push(btn);
      buttonFlag ++;
      if(buttonFlag == buttonLength){
        buttonFlag = 0;
        console.log('button2',buttonArray);
		buttonArray.splice(0,4);
      };
    };
  }); //蓝色*/
//});

$.end(function() {

});
