var content = document.querySelector(".main iframe");

(function()
{
	var url 	= window.location.href;
	var root 	= url.substring(0, url.lastIndexOf('/'));
	//var content = document.querySelector(".main iframe");
	var loaded 	= false;
	
	function updateFrame()
	{
		var page = window.location.hash;
		
		if (page != "")
			content.src = root + "/page/" + page.substring(1) + ".html";
		else
			content.src = root + "/page/default.html";
	}
	
	
	window.addEventListener("hashchange", updateFrame);
	
	window.addEventListener("message", function(event)
	{
		var data = event.data;
		
		document.title 			= data.title + " - Quack";
		content.style.height 	= (data.height + 48) + "px";
	});
	
	updateFrame();
})();