function Component(){
}

Component.prototype.createOperations = function() {
    component.createOperations();
	if (installer.isInstaller()) {
		component.addOperation("CreateShortcut", "@TargetDir@/bin/SHShare.exe", "@DesktopDir@/SHShare.lnk", "workingDirectory=@TargetDir@");
		component.addOperation("CreateShortcut", "@TargetDir@/bin/SHShare.exe", "@StartMenuDir@/SHShare.lnk", "workingDirectory=@TargetDir@");
		component.addOperation("CreateShortcut", "@TargetDir@/maintenancetool.exe", "@StartMenuDir@/maintenancetool.lnk", "workingDirectory=@TargetDir@");
		addFirewallRules();
	}
}

function addFirewallRules() {
	const program = `program=${installer.value("TargetDir")}/bin/SHShare.exe`.split('/').join('\\');
	component.addElevatedOperation("Execute", "netsh", "advfirewall", "firewall", "add", "rule", "name=@ProductName@", "protocol=TCP", "dir=in", "action=allow",  program);
    component.addElevatedOperation("Execute", "netsh", "advfirewall", "firewall", "add", "rule", "name=@ProductName@", "protocol=TCP", "dir=out", "action=allow", program);
	component.addElevatedOperation("Execute", "netsh", "advfirewall", "firewall", "add", "rule", "name=@ProductName@", "protocol=UDP", "dir=in", "action=allow",  program);
    component.addElevatedOperation("Execute", "netsh", "advfirewall", "firewall", "add", "rule", "name=@ProductName@", "protocol=UDP", "dir=out", "action=allow", program);
}