<?php
    session_start();
    if($_SESSION['permission'] != "teacher")
    {
        header("Location: index.php");
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>My Class</title>

<style>
    <?php
        include 'reset.css';
        include 'myClass-style.css';
    ?>
</style>
</head>
<body>
    <?php
    include 'config.php';

    $query = $connection->prepare("SELECT school_id, LastName, Firstname, Level_1, Level_2 FROM users WHERE PermissionLevel = 'student'");
    $query->execute();
    echo "<table id = 'myClass-Table'>
    <tr>
        <th>Student ID</th>
        <th>Level 1</th>
        <th>Level 2</th>
    </tr>";

    foreach($query as $result)
    {
        echo "<tr>";
        echo "<td>" . $result['school_id'] . "</td>";
        echo "<td>" . $result['Level_1'] . "</td>";
        echo "<td>" . $result['Level_2'] . "</td>";
        echo "</tr>";
    }
    echo "</table>";
    ?>
</body>
</html>
