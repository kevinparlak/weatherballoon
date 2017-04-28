<!DOCTYPE html>
<html>
<head>

</head>
<body>

<h1>WELCOME </h1>
<p> This the the AERSP 440  BLUE TEAM Project Home page. </p>

<form name="login" action="GuestUI.php">
            Username<input type="text" name="userid"/>
            Password<input type="password" name="pswrd"/>
            <input type="button" onclick="check(this.form)" value="Login"/>
            <input type="reset" value="Cancel"/>
            <input type="submit" value="Guest" />
        </form>

        <script language="javascript">
            function check(form) {
                if(form.userid.value == "TeamBlue" && form.pswrd.value == "rosebowl") {
                    window.open('UI.php')
                }
                else {
                    alert("Error Password or Username.")
               }
            }
        </script>

</body>
<!html>
