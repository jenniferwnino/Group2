<?php
include 'config.php';

session_start();

if(isset($_POST['username']))
{
$username = $_POST['username'];
$password = $_POST['password'];
}

$query = $connection->prepare("SELECT FirstName, PermissionLevel FROM users WHERE school_id=:username and password=:password");
$query->bindParam("username", $username);
$query->bindParam("password", $password);
$query->execute();
if ($query->rowCount() == 1)
{
    $_SESSION['username'] = $username;
    $_SESSION['password'] = $password;
    foreach ($query as $results)
    {
        $_SESSION['permission'] = $results['PermissionLevel'];
    }

    if ($_SESSION['permission'] == "teacher")
    {
       header("Location: dashboard.php");
    }
}
?>

<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="reset.css">
    <link rel="stylesheet" href="login-style.css">
    <title>Climate Stompers</title>
</head>
<body>
<div id="main">
    <form id="login-form" method="post">
        <h1>Login</h1>
        <input type="text" name="username" id="username-field" class="login-form-field" placeholder="School ID">
        <input type="password" name="password" id="password-field" class="login-form-field" placeholder="Password">
        <input type="submit" value="Login" id="login-form-submit">
    </form>
</div>
</body>
</html>