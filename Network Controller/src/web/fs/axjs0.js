var submitType = 0;

function res() {
  if (confirm("Device restroe! continue?")) {
  	window.location.href="msgrestore.htm";
  }
}

function reb() {
  if (confirm("Device reboot! continue?")) {
  	window.location.href="msgreboot.htm";
  }
}
function jump2securoty() {
  	window.location.href="security.htm";
  }
function setSubmitType(i) {
	submitType = i;
}

function checkNumberRange(inValue, minValue, maxValue) {
	if (isNaN(inValue) || (inValue < minValue) || (inValue > maxValue)) return false;
	else return true;
}
	
function ChkIp(s) {
	var i;
	var split_s = s.split(".");
	var dotCnt = split_s.length;
	if (dotCnt != 4) return -1;
	for (i=0; i<dotCnt ; i++) {
		if ((split_s[i].length > 3) || (split_s[i].length == 0)) return -1;
		if (isNaN(split_s[i]) || split_s[i] > 255 || split_s[i] < 0) return -1;
			}
	return split_s;
		}

function ChkIpFormat(s) {
	var i, j=0;
	for (i=0; i<s.length; i++) {
		if (s[i] != '.' && isNaN(s[i]))	return false;
			}
	return true;
		}

function chkForm(index) {
	var items = document.forms[index].elements;
	var i, errFlag = 0, groupErrFlag = 0;
	for (i = 0; i < items.length; i ++) {
		var errMsg = "";
		switch (items[i].name) {
		case "c_desport":
		case "s_lstport":
			if (checkNumberRange(items[i].value, 1024, 65535) == false){errMsg = " Invalid";}
			break;
		case "txtimer":
			if (checkNumberRange(items[i].value, 10, 65535) == false){errMsg = " Invalid";}
			break;
		case "static_ip":
		case "gateway_ip":
		case "dns_ip":
		case "tftps_ip":
			var ip = ChkIp(items[i].value);
			if (ip == -1 || ip[3]=="255" || ip[3]=="0"){errMsg = " Invalid";}
			break;
		case "acc_ip1":
		case "acc_ip2":
		case "acc_ip3":
		case "acc_ip4":
			if (items[i].value == "0.0.0.0") break;
			var ip = ChkIp(items[i].value);
			if (items[i].value == "" || ip == -1 || ip[3]=="255" || ip[3]=="0"){errMsg = " Invalid";}
			break;
		case "mask":
			var ip = ChkIp(items[i].value);
			if (ip == -1 || ip[0]=="0" || ip[1]=="0"){errMsg = " Invalid";}
			break;
		case "email_from":
		case "new_usn":
		case "old_psw":
		case "new_psw":
		case "cfm_psw":
		case "username":
		case "password":
		case "txtimer":
		case "file_name":
			if (items[i].value == ""){errMsg = " Invalid";}
			break;
		case "c_deshn":
		case "email_addr":
			if (items[i].value == "") {
				errMsg = " Invalid";
			}else if (ChkIpFormat(items[i].value) == true) {
				var ip = ChkIp(items[i].value);
				if (ip == -1 || ip[3]=="255" || ip[3]=="0"){errMsg = " Invalid";}
		}
			break;
		default:
			continue;	break;
	}
		document.getElementById(items[i].name + "_msg").innerHTML = errMsg;
		if (errMsg != "") errFlag = 1;
}

	if (errFlag) return false;
	
	switch (submitType)
{
	case 1:
		if (!confirm("To submit configuration! continue?")) return false;
		break;
	case 2:
		if (!confirm("The device will perform firmware update mission, please to confirm your TFTP server IP and file name again.\r\npress ok to continue, otherwise press cancel to close this window.")) return false;
		break;
	default:
		return true;
		break;
	}
}


