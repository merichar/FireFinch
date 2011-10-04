function FinchTestGo() {
	try {
		netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");
		var cid = "@rfmedialab.net/XPCOMFinch/Finch;1";
		var obj = Components.classes[cid].createInstance(Components.interfaces.IFinch);
	
	} catch (err) {
		alert(err);
		return;
	}
	/* var res = obj.getTemperature();
	alert('Reading Temperature Returned ' + res + '.');
	*/
	var ret = obj.setMotors(200,200);
}
