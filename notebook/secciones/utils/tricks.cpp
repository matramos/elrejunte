//Cantidad de decimales
cout << setprecision(2) << fixed;
//Rellenar con espacios(para justificar)
cout << setfill(' ') << setw(3) << 2 << endl;
//Leer hasta fin de linea
//  hacer cin.ignore() antes de getline()
while(getline(cin, line)){
  istringstream is(line);
  while(is >> X)
    cout << X << " ";
  cout << endl;
}
