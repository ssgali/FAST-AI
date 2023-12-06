document.addEventListener("DOMContentLoaded", function() 
{
	var l_in = sessionStorage.getItem("logged_in");
	if(l_in == "true")
	{
		location.href = "main.html"
	}
});