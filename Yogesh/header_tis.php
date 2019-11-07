<?php  $_SESSION['prevPage'] = $_SERVER['REQUEST_URI']; ?>
<header>
	<nav class="navbar navbar-inverse">

		<div class="container-fluid">
			<div class="navbar-header">
				<button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#myNavbar">
					<span class="icon-bar"></span>
					<span class="icon-bar"></span>
					<span class="icon-bar"></span>
				</button>
				<a class="navbar-brand" href="../index_tis.php">
					<img src="/images/TIS_Logo.png" alt="Traveler Information System">
				</a>
			</div>
			<div class="collapse navbar-collapse" id="myNavbar">
				<ul class="nav navbar-nav" >
					<li class="active"><a href="../index_tis.php"> Travler Information System </a></li>
				</ul>
			</div>
		</div>
	</nav>
</header>
<script src="https://unpkg.com/sweetalert/dist/sweetalert.min.js"></script>
<script>
$(function() {
	$('#logout').on('click', function() {
		$.ajax({
			url: "/logout.php",
		}).done(function() {
			location.reload(true);
		}).fail(function() {
			swal("Oops", " Something went wrong ", "error");			
		});
	});
});
</script>	