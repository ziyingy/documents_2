/**
 importRemoteFile
 */
function importRemoteFile(url) {
    var xmlhttp;
    xmlhttp = new XMLHttpRequest();
    xmlhttp.open('GET', url, false);
    xmlhttp.send();
    mioStr = xmlhttp.responseText;
    //console.log(mioStr);
    return mioStr;
}

function print() {
    console.log("AAA");
}

/**
 getUA
 */
function getUA() {
    my_json = [{
        'browserCodeName' : navigator.appCodeName,
        'browserName' : navigator.appName,
        'browserVersion' : navigator.appVersion,
        'userAgent' : navigator.userAgent,
        'screenWidth' : screen.width,
        'screenHeight' : screen.height,
        'platform' : navigator.platform
    }];
    return my_json;
}

/**
 Count the number of the word in a string
 */
function countWords(s) {
    s = s.replace(/(^\s*)|(\s*$)/gi, "");
    //exclude  start and end white-space
    s = s.replace(/[ ]{2,}/gi, " ");
    //2 or more space to 1
    s = s.replace(/\n /, "\n");
    // exclude newline with a start spacing
    return s.split(' ').length;
}

/**
 Return an array with a random combination of letters s,m,l
 */
function getRandomImageArray() {
    var imgs = ["l", "m", "s"];
    var array = [];
    for (var i = imgs.length; i >= 0; i--) {
        var n = Math.floor(Math.random() * i);
        array.push(imgs[n]);
        imgs.splice(n, 1);
    }
    return array;
}

function getQuestion(url, id_topic) {
    var objQuestion = new Object();

    str = importRemoteFile(url);
    parser = new DOMParser();
    xmlDoc = parser.parseFromString(str, "text/xml");
    idData = xmlDoc.getElementsByTagName("topic");

    for ( i = 0; i < idData.length; i++) {
        if (idData[i].getAttribute("id") == id_topic) {
            objQuestion.question = idData[i].getElementsByTagName("Q")[0].textContent;
            risposte = idData[i].getElementsByTagName("A");
            var answer = [];
            for ( j = 0; j < 4; j++) {
                answer.push(risposte[j].textContent);
                if (risposte[j].getAttribute("gold") == "true") {
                    objQuestion.correct = j;
                }
            }
            objQuestion.answers = answer;
        }
    }
    return objQuestion;
}

function getDocH(url, id_topic) {
    str = importRemoteFile(url);
	//console.log(str)
    parser = new DOMParser();
    xmlDoc = parser.parseFromString(str, "text/xml");
    idData = xmlDoc.getElementsByTagName("topic");
	console.log(idData)
	console.log(idData.length)
    for ( i = 0; i < idData.length; i++) {
		console.log(id_topic)
		console.log("id topic: " + id_topic)
		console.log("Attributo: " + idData[i].getAttribute("id"))
        if (idData[i].getAttribute("id") == id_topic) {
			
			console.log("ECCO: " +idData[i].getElementsByTagName("H")[0].textContent)
            return idData[i].getElementsByTagName("H")[0].textContent;
        }
    }
    return null;
}

function getDocN(url, id_topic) {
    str = importRemoteFile(url);
    parser = new DOMParser();
    xmlDoc = parser.parseFromString(str, "text/xml");
    idData = xmlDoc.getElementsByTagName("topic");
    for ( i = 0; i < idData.length; i++) {
        if (idData[i].getAttribute("id") == id_topic) {
            return idData[i].getElementsByTagName("N")[0].textContent;
        }
    }
    return null;
}

/*
function isNumberOrDot(event) {
    if (event) {
        var charCode = event.keyCode;
        if ((charCode > 47 && charCode < 58) || charCode == 190 || charCode == 46 || charCode == 8 || charCode == 9)
            return true;
    }
    return false;
}
*/

function isNumberOrDot(event) {
	if (event) {
		var charCode = (event.charCode) ? event.charCode : ((event.which) ? event.which : event.keyCode);
		if ((charCode > 47 && charCode < 58) || charCode == 190 || charCode == 46 || charCode == 8 || charCode == 9)
			return true;
		}
	return false;
}


function injectInstructions(string) {
    $(".well > p ").html(string);
}

function expandInstructions() {

    var well = document.getElementsByClassName("well")[0];
     $(".well").slideDown("slow");
}

function closeInstructions() {

    var well = document.getElementsByClassName("well")[0];
     $(".well").slideUp("fast");
}

function setResult(result) {
    $(".text_result")[0].value = result;
}

function showEnd(show) {
    if (show) {
        if ($('.form-actions')[0] != null) {
            $('.form-actions')[0].show();
        }
        if ($('.btn-cf-blue')[0] != null) {
            $('.btn-cf-blue')[0].show();
        }

    } else {
        if ($('.form-actions')[0] != null) {
            $('.form-actions')[0].hide();
        }
        if ($('.btn-cf-blue')[0] != null) {
            $('.btn-cf-blue')[0].hide();
        }
    }
}

