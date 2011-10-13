function FinchTestBackward() {
	try {
		netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");
		var cid = "@tutortechnologies.com/FireFinch/Finch;1";
		var obj = Components.classes[cid].createInstance(Components.interfaces.IFinch);

	} catch (err) {
		alert(err);
		return;
	}
	var ret = obj.setMotors(-200,-200);
}
function FinchTestForward() {
	try {
		netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");
		var cid = "@tutortechnologies.com/FireFinch/Finch;1";
		var obj = Components.classes[cid].createInstance(Components.interfaces.IFinch);

	} catch (err) {
		alert(err);
		return;
	}
	var ret = obj.setMotors(200,200);
}
function FinchTestRight() {
	try {
		netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");
		var cid = "@tutortechnologies.com/FireFinch/Finch;1";
		var obj = Components.classes[cid].createInstance(Components.interfaces.IFinch);

	} catch (err) {
		alert(err);
		return;
	}
	var ret = obj.setMotors(200,000);
}
function FinchTestLeft() {
	try {
		netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");
		var cid = "@tutortechnologies.com/FireFinch/Finch;1";
		var obj = Components.classes[cid].createInstance(Components.interfaces.IFinch);

	} catch (err) {
		alert(err);
		return;
	}
	var ret = obj.setMotors(000,200);
}
function FinchTestStop() {
	try {
		netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");
		var cid = "@tutortechnologies.com/FireFinch/Finch;1";
		var obj = Components.classes[cid].createInstance(Components.interfaces.IFinch);

	} catch (err) {
		alert(err);
		return;
	}
	var ret = obj.setMotors(0,0);
}
