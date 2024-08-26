
use rand::Rng;

fn main() {
    // Performance Tunables
    // If the memory isn't in cache it incurs a large performance penalty
    // 'Pre-caching' or 'pre-fetching' is act of getting the memory ahead of time.
    // Failing to find memory in cache is called a 'cache miss'
    let precache = false;

    // If other operations do operations that need large amounts of cache it will evict
    // previous cache lines, thereby degrading performance. This is why locality is important
    let crush_the_cache = true;
    println!("Precaching Enabled: {precache}\nCache Crushing Enabled: {crush_the_cache}");

    let mut map = std::collections::HashMap::<usize, u64>::new();
    let mut vec = Vec::<(usize, u64)>::new();
    let mut r = rand::thread_rng();

    vec.resize(1000, (0, 0));
    vec.resize(0, (0, 0));
    for i in 0..1000_u64 {
        let key: usize = r.gen();
        map.insert(key, i);
        vec.push((key, i));
    }

    let mut cache_crusher = Vec::<u64>::new();

    // Obliterates the CPU cache and invalidates everything
    if crush_the_cache
    {
        let crush_start = std::time::Instant::now();
        let random: u64 = r.gen();
        cache_crusher.resize(32_000_000, random);
        for i in 1..100_000
        {
            let r_i: u64 = r.gen_range(0..32_000_000);
            cache_crusher[ r_i as usize ] = random * 64;
        }
        cache_crusher[152_010] = r.gen();
        let crush_elapsed = crush_start.elapsed();
        println!("crush elapsed: {crush_elapsed:?}");
    }

    // Setup entries to find
    let random_entries = [69, 23, 42, 15, 152];
    println!("Lookup Entries");
    for x in random_entries
    {
        map.insert(x, x as u64);
        map.get(&x);
        println!("{x}");
        let random: usize = r.gen_range(0..1000);
        vec[ random ] = (x, x as u64);
    }
    vec[50] = (0, 69);
    println!("");

    let i = std::time::Instant::now();
    let result = map.get(&69).unwrap();
    let elapsed = i.elapsed();
    println!("map single lookup: {elapsed:?}");

    // Pre-fetch all of 'vec' again to ensure the cache is hot and avoid cache misses
    if precache
    {
        let mut tmp = Vec::<(usize, u64)>::new();
        tmp.resize(1000, (0,0));
        tmp.resize(0, (0,0));
        for i in 1..1000
        {
            tmp.push( vec[i] );
        }
    }
    // Loop Varient
    let mut count = 0;
    let i = std::time::Instant::now();
    for (k, v) in &vec
    {
        count += 1;             // Comment for performance
        if (*k == 69) { break; }
    }
    let elapsed = i.elapsed();
    println!("vec single lookup loop: {elapsed:?}");
    println!("vec iterations: {count}");

    // find() variant
    let mut count = 0;
    let i = std::time::Instant::now();
    let _result = vec.iter().find(|(key, v)| { count += 1; *key == 69} ).unwrap();
    let elapsed = i.elapsed();
    println!("vec single lookup find() function reference: {elapsed:?}");
    println!("vec iterations: {count}");

    // Multiple entry hash-varient
    let mut count = 0;
    let mut _map_results = Vec::<u64>::new();
    _map_results.reserve(100);

    let i_hm = std::time::Instant::now();
    for i in random_entries
    {
        count += 1;
        _map_results.push( *map.get(&i).unwrap() );
    }
    let elapsed_hm = i_hm.elapsed();
    println!("map multiple lookups: {elapsed_hm:?}");
    println!("map iterations: {count}");
    println!("map read for deoptimizaiton: {_map_results:?}");
}
