open ApolloHooks;
open Belt;

module GetExchangeRates = [%graphql
  {|
  query getExchangeRates {
    rates(currency: "USD") {
      currency
      rate
    }
  }
|}
];

[@react.component]
let make = () => {
  let (simple, _full) = useQuery(GetExchangeRates.definition);

  <div>
    {switch (simple) {
     | Loading => <p> {React.string("Loading...")} </p>
     | Data(data) =>
       let currencies =
         switch (data##rates) {
         | Some(rates) =>
           rates->Array.map(rate =>
             rate
             ->Option.flatMap(rate => rate##currency)
             ->Option.mapWithDefault(React.null, currency =>
                 <p> {React.string(currency)} </p>
               )
           )
         | None => [||]
         };
       React.array(currencies);
     | NoData
     | Error(_) => <p> {React.string("Get off my lawn!")} </p>
     }}
  </div>;
};