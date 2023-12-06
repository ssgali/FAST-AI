
document.addEventListener("DOMContentLoaded", function()  // Function is called when any Webpage is loaded 
{
	var l_in = sessionStorage.getItem("logged_in");
	if(l_in == "true")
	{
	removebuttons();
	}
	else if(l_in == "false")
	{
		logout();
	}
}
);
function login() //Validating Log In
{
  let a = document.getElementById("ab").value;		//Getting ID
  let b = document.getElementById("cd").value;		//Getting Password
  if (a == "alirauf660@gmail.com" && b == "abc") {
    location.href = "main.html";
  } else if (a == "mdsoban680@gmail.com" && b == "fast-321") {
    location.href = "main.html";
  } else if (a == "saim786@gmail.com" && b == "pakistan-123") {
    location.href = "main.html";
  } else {
    alert("Invalid Credentials!");
    location.href = "login.html";
    return;
  }
  sessionStorage.setItem("logged_in", true);
  removebuttons();
}
function signup()  // Validating Sign Up
{
  let a = document.getElementById("el").value;			//Getting Values
  let b = document.getElementById("pass").value;
  let c = document.getElementById("pass1").value;
  let d = document.getElementById("dob").value;
  if (b != c) {
    alert("Passwords Don't Match!");
    location.href = "signup.html";
    return;
  }
  if (!a.includes("@gmail.com")) {
    alert("Please Enter a Valid Email Address!");
    location.href = "signup.html";
    return;
  }
  var new_date = new Date(d);
  new_date = parseInt(new_date.getFullYear());
  new_date = 2023 - new_date;
  if (new_date < 18) {
    alert("Age Below 18!");
    location.href = "signup.html";
    return;
  } else {
    logged_in = true;
    alert("New User Made!");
    location.href = "main.html";
  }
  removebuttons();
}
function removebuttons() //Remove Buttons throughout the pages
{
	var elementsToRemove = document.getElementsByClassName("remove");
	  for (var i = 0; i < elementsToRemove.length; i++) 
	  {
		elementsToRemove[i].classList.add("hide");
	  }
	var er = document.getElementsByClassName("remove_lo");
	  for (var i = 0; i < er.length; i++) 
	  {
		er[i].classList.add("show");
	  }
}
function check()  // For checking if the user is logged in or not ? to view the  cart
{
  var logged_in = sessionStorage.getItem("logged_in");
  if (logged_in == "true") {
    location.href = "cart.html";
  } else {
    alert("Please Log In to View Cart!");
    location.href = "login.html";
  }
}
function check1()  // For checking if the user is logged in or not ? to view the  cart
{
  var logged_in = sessionStorage.getItem("logged_in");
  if (logged_in == "true") {
    add_movies();
  } else {
    alert("Please Log In to Book!");
    location.href = "login.html";
  }
}
function check_card() // Card Validating 
{
  var card = parseInt(document.getElementById("card_num").value);
  var cvv = parseInt(document.getElementById("cvv").value);
  if ((cvv === 141 || cvv === 121) && (card === 1234567891011234 || card === 4321110987654321)) 
  {
    alert("Payment Successful!\nYou can Collect your tickets from the Venue!");
	reset_cart()
	location.href = "cart.html";
  } 
  else 
  {
    alert("Invalid Data Entered!");
    return;
  }
}

function logout() //For logging out and restoring buttons
{
	sessionStorage.setItem("logged_in", false);
	var er = document.getElementsByClassName("show");
	  for (var i = 0; i < er.length; i++) 
	  {
		er[i].classList.add("hide");
	  }
	if(sessionStorage.getItem("cart_items") !== null)
	{
		reset_cart()
	}
}
function populate_cart()    // Adding items to the cart
{
	var fill_items = sessionStorage.getItem("fill_cart");
  var cart_items = sessionStorage.getItem("cart_items");
  var items = JSON.parse(cart_items);
  let tbody = document.getElementById("table_id");
  let subtotal = document.getElementById("subtotal");
  var html = [];
  var total = parseInt(0);
  for (var i = 0; i < items.length; i++) {
    const item = items[i];
    html.push(`<tr>
  	     	<td> <img src="${item.image}"> </td>
  	     	<td>
  	     		<h5>${item.name}</h5></td>
  	     		<td> <h5> Rs. ${item.price}</h5> </td>
  	     		<td>${item.quantity}</td>
  	     		<td><h5> Rs.${item.total}</h5> </td>
  	     	</tr>
  	     <tr>`);
		 var total = total + item.total;
  }
  subtotal.innerHTML = "Rs. " + total;
  tbody.innerHTML = html.join("");  // Adding all of the string from the tbody id aka table from the HTML file
}
function add_movies()
{
	var quant = parseInt(1);
	var prices = parseInt(1000);
	var names = document.getElementById("name").textContent;
	var items = [];
	if(JSON.parse(sessionStorage.getItem("cart_items")) !== null)
	{
		items = JSON.parse(sessionStorage.getItem("cart_items"));
	}
	items.push({image: "./images/movie.png", name: names, price: prices, quantity: quant, total: prices});
	sessionStorage.setItem("cart_items", JSON.stringify(items));
	location.href = "cart.html";
}
function reset_cart()  // Reseting card to zero items
{
	sessionStorage.removeItem("cart_items"); // removing all of the string from the tbody id aka table from the HTML file
	location.reload();
}
function validate_check()   // Getting values from the refreshment page
{
  var logged_in = sessionStorage.getItem("logged_in");
  if (!logged_in) {
    alert("Please Log In to View Cart!");
    location.href = "login.html";
    return;
  }
  var pizza = parseInt(document.getElementById("pizza").value);
  var burger = parseInt(document.getElementById("burger").value);
  var coffee = parseInt(document.getElementById("coffee").value);
  var mex_hd = parseInt(document.getElementById("mex_hd").value);
  var cake = parseInt(document.getElementById("cake").value);
  var chick = parseInt(document.getElementById("chick").value);
  var drinks = parseInt(document.getElementById("drinks").value);
  var m_snack = parseInt(document.getElementById("m_snack").value);
  var pop = parseInt(document.getElementById("pop").value);
  if (pop < 0 || m_snack < 0 || drinks < 0 || cake < 0 || chick < 0 || coffee < 0 || burger < 0 || pizza < 0 || mex_hd < 0) {
    alert("Cannot Enter Negative Value!");
    return;
  }
  if (pop > 10 || m_snack > 10 || drinks > 10 || cake > 10 || chick > 10 || coffee > 10 || burger > 10 || pizza > 10 || mex_hd > 10) {
    alert("Maximum Value is 10!");
    return;
  }
  if (isNaN(pop) && isNaN(m_snack) && isNaN(drinks) && isNaN(cake) && isNaN(coffee) && isNaN(burger) && isNaN(pizza) && isNaN(mex_hd) && isNaN(chick)) {
    alert("Cannot add Zero things to cart!");
    return;
  }
  var images = ["./images/popcorn.jpg"
  ,"./images/hotdog.jpeg"
  ,"./images/frychick.jpg"
  ,"./images/drinks.jpg"
  ,"./images/cake.jpg"
  ,"./images/coffee.jpg"
  ,"./images/burger.jpg"
  ,"./images/snacks.jpg"
  ,"./images/pizza.jpeg"];
  var name = ["Popcorn", "Mexican Hotdog", "BBQ Chicken", "Drinks", "Cake", "Coffee", "Burger", "Mixed Snack", "Pizza"];
  var arr = [pop * 500, mex_hd * 600, chick * 550, drinks * 250, cake * 300, coffee * 200, burger * 400, m_snack * 350, pizza * 1000];
  var price = [500, 600, 550, 250, 300, 200, 400, 350, 1000];
  var quantity = [pop, mex_hd, chick, drinks, cake, coffee, burger, m_snack, pizza];
  var items = [];
	if(JSON.parse(sessionStorage.getItem("cart_items")) !== null)
	{
		items = JSON.parse(sessionStorage.getItem("cart_items"));
	}
	for (var i = 0; i < 9; i++) {
    if (arr[i] > 0) {
      items.push({ image: images[i], name: name[i], price: price[i], quantity: quantity[i], total: arr[i] }); // Adding items to Array 
    }
  }
  sessionStorage.setItem("cart_items", JSON.stringify(items)); // converting whole array into a string 
  location.href = "cart.html";
}
function check_cart()
{
	var check = sessionStorage.getItem("cart_items");
	if(check === null)
	{
		alert("Empty Cart!");
		return;
	}
	else
	{
		location.href = "payment.html";
	}
}
if (document.body.id === "cart_page") 
{
  populate_cart();
}
