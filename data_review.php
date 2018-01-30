<?php 
    // Include MySQL Connection
    include('dbconnect.php');
?>

<html>
<head>
    <!-- Title -->
    <title>SPK LPG</title>
    <link rel="icon" type="image/png" href="img/logo.png">
    <!-- Include -->
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width">
    <link rel="stylesheet" href="css/bootstrap.min.css">
    <script type="text/javascript" src="js/bootstrap.min.js"></script>
    <link href="css/style.css" rel="stylesheet">
    <link href="css/table.css" rel="stylesheet">
</head>

<body>
    <!-- Header -->
    <div class="header">
        <ul class="nav nav-pills pull-right">
          <li role="presentation" class="active">
            <a href="index.html">Home</a>
          </li>
        </ul>
        <h3 class="text-muted">SPK LPG</h3>
    </div>
    <!-- Container --> 
    <div class="container">
        <div class="jumbotron">
        <h1><p style="font-size:36px">Status Gas LPG</p></h1>
<?php
    // Retrieve newest record
    $result = mysqli_query($dbh, "SELECT * FROM detektor ORDER BY id_detektor DESC LIMIT 1");
    // Process and show record
    while($row = mysqli_fetch_array($result))
    {
        echo '<div class="well">';
        echo date("j F Y g:i a", strtotime($row["timestamp"]));
        echo '</div>';
        if (($row["nilai_sensor_api"] >= 625) || ($row["nilai_sensor_gas"] >= 850)) {
            $situasi = 'Perlu Penanganan Segera';
        } else {
            $situasi = 'Aman';
        }
        echo '<div class="panel panel-default">';
        echo '<div class="panel-heading">';
        echo '<h3 class="panel-title">Status Gas LPG</h3>';
        echo '</div>';
        echo '<div class="panel-body">';
        echo $situasi;
        echo '</div>';
        echo '</div>';
        if (($row["nilai_sensor_api"] >= 625) && ($row["nilai_sensor_gas"] >= 850)) {
        	$kondisi = 'Terjadi Kebakaran dan Kebocoran Gas. Perlu Dilakukan Penanganan dan Pemadaman Segera!';
        } else if ($row["nilai_sensor_api"] >= 625) {
            $kondisi = 'Terjadi Kebakaran. Perlu Dilakukan Pemadaman Segera!';
        } else if ($row["nilai_sensor_gas"] >= 850) {
            $kondisi = 'Terjadi Kebocoran Gas. Perlu Dilakukan Penanganan Segera!';
        } else {
        	$kondisi = "Gas LPG Beroperasi Normal";
        }
        echo '<div class="panel-footer">';
        echo $kondisi;
        echo '</div>';
        echo '<br>';
        echo '<div class="btn-group">';
        echo        '<a href="data_review.php"><button class="btn btn-default">Refresh</button></a>';
        echo '</div>';
        echo '</div>';

    }
?>
        </div>
    </div>
    <!-- Footer -->
    <div class="footer">
      <p>&copy; 42K4 2018</p>
    </div>
</body>

</html>