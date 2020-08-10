// ============================================================================================================================
// Controller
// ============================================================================================================================

var Controller = (function()
{
	window.parent.postMessage({
		msg: "contentInfo",
		title: document.title,
		height: document.body.scrollHeight
	}, "*");

	if (window.self === window.top)
	{
		var match = /\/([^./]+).html/.exec(window.location.href);
		
		var notice = document.createElement("a");
		notice.innerHTML = "See Full Context";
		notice.href = "../index.html#" + match[1];
		
		document.body.insertBefore(notice, document.body.children[0]);
	}

	window.addEventListener("message", function(event)
	{
		var data = event.data;

		switch (data.msg)
		{
			case "show":
				
				break;
		}
	});
})();

// ============================================================================================================================
// Highlighter
// ============================================================================================================================

var Highlighter = (function()
{
	var rxNotAlphaNumeric 	= /[^A-Za-z0-9]/g;
	var rxNotAlpha 			= /[^A-Za-z]/g;
	var rxNotNumeric		= /[^0-9.]/g;
	var rxDoubleQuote		= /([^\\])"/g;
	var rxSingleQuote		= /([^\\])'/g;
	var rxNewLine			= /\n/g;
	var rxEndComment		= /\*\//g;
	var rxTab				= /\t/g;
	var keywords 			= {
		"identifier": 	"identifier special",
		"type": 		"datatype special",
		"void": 		"datatype",
		"bool": 		"datatype",
		"int": 			"datatype",
		"float": 		"datatype",
		"string": 		"datatype",
		"auto": 		"datatype",
		"if": 			"keyword",
		"for": 			"keyword",
		"while": 		"keyword",
		"do": 			"keyword",
		"return": 		"keyword",
		"yield": 		"keyword",
		"true": 		"literal",
		"false": 		"literal",
		"cycle":		"async",
		"ms":			"async",
		"s":			"async",
		"until":		"async"
	};
	
	function getPart(code, rx, start, result)
	{
		rx.lastIndex = start + 1;
		var match = rx.exec(code);
		
		if (match != null)
		{
			result.text 	= code.substring(start, match.index);
			result.index 	= match.index;

			if (match.length > 1)
				result.text = result.text + match[1];
		}
		else
		{
			result.text 	= code.substring(start);
			result.index 	= code.length;
		}
	}
	
	function format(code)
	{
		var source = code.innerHTML;
		var output = "";
		var result = {text: "", index: 0};
		var k, c;
		var limit = 500;
		
		for (var i = 0, s = source.length; i < s; ++i)
		{
			c = source[i];
			
			if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <='z'))
			{
				getPart(source, rxNotAlphaNumeric, i, result);
				i = result.index - 1;
				k = keywords[result.text];
				output += k != null ? '<span class="' + k + '">' + result.text + '</span>' : result.text;
			}
			else if ((c >= '0' && c <= '9') || c == '-' || c == '.')
			{
				getPart(source, rxNotNumeric, i, result);
				i = result.index - 1;
				output += '<span class="literal">' + result.text + '</span>';
			}
			else if (c == '"' || c == '\'')
			{
				getPart(source, c == '"' ? rxDoubleQuote : rxSingleQuote, i + 1, result);
				i = result.index + 1;
				output += c == '"' ? '<span class="literal">"' + result.text + '"</span>' : '<span class="literal">\'' + result.text + '\'</span>';
			}
			else if (c == '/')
			{
				if (i + 1 < s)
				{
					if (source[i + 1] == '/')
					{
						getPart(source, rxNewLine, i, result);
						i = result.index - 1;
						result.text = result.text.replace(rxTab, "  ");
						output += '<span class="comment">' + result.text + '</span>';
					}
					else if (source[i + 1] == '*')
					{
						getPart(source, rxEndComment, i, result);
						i = result.index + 1;
						result.text = result.text.replace(rxTab, "  ");
						output += '<span class="comment">' + result.text + '*/</span>';
					}
					else
						output += c;
				}
				else
					output += c;
			}
			else if (c == '\t')
				output += '  ';
			else
				output += c;
			
			if (--limit <= 0)
				break;
		}
		
		code.innerHTML = output;
		
		var b 			= code.getBoundingClientRect();
		var lineCount	= b.height / 24 + 1;
		var lineNumbers = document.createElement("div");
		
		output = "";
		for (var i = 1; i < lineCount; ++i)
			output += i + "<br />";
		
		lineNumbers.className = "lines";
		lineNumbers.innerHTML = output;
		code.parentNode.appendChild(lineNumbers);
	}
	
	var code = document.querySelectorAll("div.def > pre");
	for (var i = 0; i < code.length; ++i)
		format(code[i]);
	
	function linkKeyword(special)
	{
		
	}
	
	var special = document.querySelectorAll(".special");
	for (var i = 0; i < special.length; ++i)
		linkKeyword(special);
})();