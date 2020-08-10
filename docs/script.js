var content = document.querySelector(".main iframe");

(function()
{
	var url		= window.location.href;
	var root	= url.substring(0, url.lastIndexOf('/'));
	var is404	= false;
	var loader	= document.createElement("div");

	loader.classList.add("loader");

	function loadBegin()
	{
		content.parentElement.append(loader);
		content.classList.add("loading");
	}

	function loadEnd()
	{
		loader.remove();
		content.classList.remove("loading");
	}
	
	function refresh()
	{
		var page = window.location.hash;

		is404 = false;
		
		if (page != "")
			content.src = root + "/page/" + page.substring(1) + ".html";
		else
			content.src = root + "/page/default.html";

		loadBegin();
	}
	
	content.addEventListener("load", function(event)
	{
		if (content.src.indexOf("not_found.html") >= 0)
		{
			loadEnd();
			return;
		}

		if (content.contentDocument != null)
		{
			var h1 = content.contentDocument.querySelector("h1");
			if (h1 != null && h1.innerText.indexOf('404') >= 0)
				is404 = true;
		}

		if (is404)
			content.src = root + "/page/not_found.html";
		else
			loadEnd();
	});

	window.addEventListener("hashchange", refresh);

	window.addEventListener("message", function(event)
	{
		var data = event.data;

		switch (data.msg)
		{
			case "contentInfo":
				document.title			= data.title + " - Quack";
				content.style.height	= (data.height + 48) + "px";
				break;
		}
	});

	refresh();
})();