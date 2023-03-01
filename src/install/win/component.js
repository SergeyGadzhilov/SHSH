function Component()
{
}

Component.prototype.createOperations = function()
{
    component.createOperations();
    component.addOperation("CreateShortcut", "@TargetDir@/bin/SHShare.exe", "@StartMenuDir@/SHShare.lnk", "workingDirectory=@TargetDir@");
	component.addOperation("CreateShortcut", "@TargetDir@/maintenancetool.exe", "@StartMenuDir@/maintenancetool.lnk", "workingDirectory=@TargetDir@");
}