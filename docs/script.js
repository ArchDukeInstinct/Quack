var content = document.querySelector(".main iframe");

(function()
{
	var url			= window.location.href;
	var root		= url.substring(0, url.lastIndexOf('/'));
	var is404		= false;
	var timer404	= null;
	var loader		= document.createElement("div");
	var hasScroll	= null;

	loader.classList.add("loader");

	function resize()
	{
		var scroll = document.body.scrollHeight > window.innerHeight;

		if (scroll != hasScroll)
		{
			document.body.classList.toggle("no-scroll", !scroll);
			hasScroll = scroll;
		}
	}

	function loadBegin()
	{
		if (timer404 != null)
			clearTimeout(timer404);

		timer404 = setTimeout(loadTimeout, 5000);

		content.parentElement.append(loader);
		content.classList.add("loading");
	}

	function loadEnd()
	{
		if (timer404 != null)
			clearTimeout(timer404);

		is404 = false;
		timer404 = null;

		loader.remove();
		content.classList.remove("loading");

		requestAnimationFrame(resize);
	}

	function loadTimeout()
	{
		if (is404)
		{
			loadEnd();
			return;
		}

		is404 = true;
		timer404 = setTimeout(loadTimeout, 5000);

		content.src = root + "/page/not_found.html";
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

	window.addEventListener("message", function(event)
	{
		var data = event.data;

		switch (data.msg)
		{
			case "pageStart":
				content.contentWindow.postMessage({msg: "init", version: "1.0"}, "*");
				break;

			case "pageFinish":
				document.title			= data.title + " - Quack";
				content.style.height	= (data.height + 48) + "px";

				loadEnd();
				break;
		}
	});

	window.addEventListener("hashchange", refresh);
	window.addEventListener("resize", resize);

	refresh();
})();