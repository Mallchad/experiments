
fn stub() -> i32
{
    return 1;
}

fn main()
{
    // Doesn't prefault
    let mut _vec: Vec<i32> = Vec::new();
    _vec.reserve( 100000000 );
    // Both touches all pages
    _vec.resize( 70000000, 0 );
    //_vec.fill( 0xDEADBE );
    stub();
}
